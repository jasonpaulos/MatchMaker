<?php
	require 'mobile.php';
	echoDoctype();
?>

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<link type="text/css" rel="stylesheet" href="styles.css" />
	<title>Welcome to Match Maker</title>
	<?php
		echoMeta();
	?>
</head>
<body>
	<div class="page">
		<h1 class="title">Match Maker</h1>
		
		<div class="content">
			<h3>Welcome to Match Maker</h3>
			
			<?php
				require 'date.php';
				
				if(isBeforeStart(time())){
					echo '<p>Registration will start on '.date('F', $startDate).' '.date('d', $startDate).'.</p>';
				}elseif(isAfterEnd(time())){
					echo '<p>Sorry, registration ended on '.date('F', $endDate).' '.date('d', $endDate).'.</p>';
				}else{
					echo '<p>Registration is open from '.date('F', $startDate).' '.date('d', $startDate).' to '.date('F', $endDate).' '.date('d', $endDate).'.</p>
						<p><a href="register.php">Click here to register for matches</a></p>';
				}
			?>
		</div>
	</div>
</body>
</html>
