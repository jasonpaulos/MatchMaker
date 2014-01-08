<?php
	require 'questions.php';
	
	$db;
	$table = 'UserInput';
	
	try{
		//SQLite: $db = new PDO('sqlite:DATABSE_NAME');
		//MySQL:
		$db = new PDO(
			'mysql:dbname=DATABASE_NAME;host=HOST',
			'USERNAME', //username
			'PASSWORD' //password
		);
	}catch(PDOException $e){
		die("Error when connecting to database: ".$e->getMessage());
	}
	
	$db->setAttribute(PDO::ATTR_EMULATE_PREPARES, false);
	$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	
	{
		$query = 
			'CREATE TABLE IF NOT EXISTS '.$table.' (
				firstName VARCHAR(20) NOT NULL,
				middleName CHAR(1) NOT NULL,
				lastName VARCHAR(20) NOT NULL,
				gender TINYINT(1),
				grade TINYINT(1)';
		for($q = 0; $q < count($questions); ++$q){
			$query .= ', q'.$q.' TINYINT(1)';
		}
		$query .= ')';
		
		$db->exec($query);
	}
?>