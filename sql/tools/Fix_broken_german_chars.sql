UPDATE `table` SET 
	`column` = REPLACE(`column`,"ÃŸ", "ß"), 
	`column` = REPLACE(`column`, "Ã¤", "ä"), 
	`column` = REPLACE(`column`, "Ã¼", "ü"), 
	`column` = REPLACE(`column`, "Ã¶", "ö"), 
	`column` = REPLACE(`column`, "Ã„", "Ä"), 
	`column` = REPLACE(`column`, "Ãœ", "Ü"), 
	`column` = REPLACE(`column`, "Ã–", "Ö"), 
	`column` = REPLACE(`column`, "â‚¬", "€")
	WHERE `language_code` = 'deDE';