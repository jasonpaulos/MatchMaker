<?php
	//Of course you would want to change the time zone to where you live
	date_default_timezone_set('America/Phoenix');
	
	$startDate = strtotime('2014-01-06 00:00:00'); //Arbitrary start date
	$endDate = strtotime('2014-01-24 23:59:59'); //Arbitrary end date
	//Because index.php refers to the date objects, you can fully change them right here
	
	function isBeforeStart($time){
		global $startDate;
		return $startDate > $time;
	}
	
	function isAfterEnd($time){
		global $endDate;
		return $endDate < $time;
	}
	
	function isValidTime($time){
		global $startDate;
		global $endDate;
		return !isBeforeStart($time) && !isAfterEnd($time);
	}
?>