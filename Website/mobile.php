<?php
	//This function decides if we should load the mobile version of the site based off the user agent
	function isMobile(){
		return preg_match("/(android|avantgo|blackberry|bolt|boost|cricket|docomo|fone|hiptop|mini|mobi|palm|phone|pie|tablet|up\.browser|up\.link|webos|wos)/i", $_SERVER["HTTP_USER_AGENT"]);
	}
	
	//Echos the correct doctype for mobile or desktop
	function echoDoctype(){
		if(isMobile()){
			echo '<!DOCTYPE html PUBLIC "-//WAPFORUM//DTD XHTML Mobile 1.0//EN" "http://www.wapforum.org/DTD/xhtml-mobile10.dtd">';
		}else{
			echo '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">';
		}
	}
	
	//This disables zooming for mobile devices
	//It's a nice feature, but it can become frustrating if information is too small
	function echoMeta(){
		if(isMobile()){
			echo '<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0"/>';
		}
	}
?>
