UPDATE `table` SET 
	`column` = REPLACE(`column`,"ß", "�"), 
	`column` = REPLACE(`column`, "ä", "�"), 
	`column` = REPLACE(`column`, "ü", "�"), 
	`column` = REPLACE(`column`, "ö", "�"), 
	`column` = REPLACE(`column`, "Ä", "�"), 
	`column` = REPLACE(`column`, "Ü", "�"), 
	`column` = REPLACE(`column`, "Ö", "�"), 
	`column` = REPLACE(`column`, "€", "�")
	WHERE `language_code` = 'deDE';