/*
 * module.hpp - Copyright (C) 2007 by Nathan Reed
 * Implementation of the module class from luabridge.hpp.
 */

/*
 * Templates generating C functions that can be registered to Lua.  These act
 * as proxies for functions that we want to register, performing the mechanics
 * of dynamic type checking and so forth.  They are registered to Lua as
 * C closures with the actual function pointer to call as an upvalue.  We have
 * to enclose them in structs so that we can specialize on the void return
 * type, since C++ doesn't allow specialization of function templates.
 */

template <typename FnPtr, typename Ret = typename fnptr<FnPtr>::resulttype>
struct function_proxy
{
    typedef typename fnptr<FnPtr>::params params;
    static int f (lua_State *L)
    {
        FnPtr fp = (FnPtr)lua_touserdata(L, lua_upvalueindex(1));
        arglist<params> args(L);
        int top = lua_gettop(L);
        tdstack<Ret>::push(L, fnptr<FnPtr>::apply(fp, args));
        return (lua_gettop(L) - top);
    }
};

template <typename FnPtr>
struct function_proxy <FnPtr, void>
{
    typedef typename fnptr<FnPtr>::params params;
    static int f (lua_State *L)
    {
        FnPtr fp = (FnPtr)lua_touserdata(L, lua_upvalueindex(1));
        arglist<params> args(L);
        int top = lua_gettop(L);
        fnptr<FnPtr>::apply(fp, args);
        return (lua_gettop(L) - top);
    }
};

/*
 * Perform function registration in a module.
 */

template <typename FnPtr>
module& module::function (FnPtr fp, const char * start, ...)
{
    va_list arglist;
    va_start(arglist, start);
    const char * name = start;
    lua_pushlightuserdata(L, (void *)fp);
    lua_pushcclosure(L, &function_proxy<FnPtr>::f, 1);
    while(name != NULL)
    {
        lua_pushvalue(L, -1);
        lua_setglobal(L, name);
        name = va_arg(arglist, const char*);
    }
    va_end(arglist);
    lua_pop(L, 1);
    return *this;
}

/*
 * Lua-registerable C function templates for getting and setting the value of
 * a global/static variable through a pointer; used as property proxies.
 * These work similiarly to the function proxies above.
 */

template <typename U>
int propget_proxy (lua_State *L)
{
    U *data = (U *)lua_touserdata(L, lua_upvalueindex(1));
    tdstack<U>::push(L, *data);
    return 1;
}

template <typename U>
int propset_proxy (lua_State *L)
{
    U *data = (U *)lua_touserdata(L, lua_upvalueindex(1));
    *data = tdstack<U>::get(L, 1);
    return 0;
}

/*
 * Perform class registration in a module.
 */

template <typename T>
class__<T> module::class_ ()
{
    return class__<T>(L);
}

template <typename T, typename Base>
class__<T> module::subclass (const char *name, bool destruct)
{
    assert(classname<Base>::name() != classname_unknown);
    return class__<T>(L, name, classname<Base>::name(), destruct);
}

template <typename T>
class__<T> module::class_ (const char *name, bool destruct)
{
    return class__<T>(L, name, destruct);
}

template <typename T>
module& module::class_decl(const char * name)
{
    classname<T>::set_name(name);
    return *this;
}
