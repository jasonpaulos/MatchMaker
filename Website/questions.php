<?php
	function createQuestion($text,
							$disagree = 'Strongly disagree',
							$agree = 'Strongly agree'){
		return (object)array('text' => $text, 'disagree' => $disagree, 'agree' => $agree);
	}
	
	function isNameValid($arg, $middleName){
		return $middleName ?
				(!empty($arg) ? preg_match('/^[a-zA-Z]$/', $arg) : true) :
				(!empty($arg) && preg_match('/^[a-zA-Z- ]+$/', $arg));
	}
	
	$questions = array(
		createQuestion(
			'I believe that this is an example question.'
		),
		createQuestion(
			'Is this an example question with custom labels?',
			'Yes it is',
			'No it is not'
		),
	);
?>
