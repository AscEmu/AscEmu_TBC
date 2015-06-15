// Replaced by dword
#ifndef _REALM_PACKET_H_
#define _REALM_PACKET_H_

class RealmPacket
{
private:
	unsigned short _size;
	unsigned char _opcode;
	unsigned char* _data;
public:
	RealmPacket(void) {}
	inline unsigned short size(void) { return _size; }
	inline unsigned char GetOpcode(void) { return _opcode; }
	inline unsigned char* contents(void) { return _data; }

};

class FileConfiguration
{
private:
	static FileConfiguration* instance;
	bool _LogRealm;
	bool _LogWorld;

	FileConfiguration(void) { _LogRealm = true; _LogWorld = true; }
	FileConfiguration(const FileConfiguration&);
	FileConfiguration& operator=(const FileConfiguration&);
	~FileConfiguration(void) {}
public:
	static FileConfiguration& getInstance(void)
	{
		if (instance == 0)
		{
			instance = new FileConfiguration;
		}

		return *instance;
	}

	bool GetBoolDefault(const char* value, bool _override/*unk: always false*/)
	{
		if (_override)
			return true;

		if (strcmp(value, "LogRealm") == 0)
			 return _LogRealm;
		else if (strcmp(value, "LogWorld") == 0)
			return _LogWorld;

		return false;
	}
};

#define sConfig FileConfiguration::getInstance()

#endif