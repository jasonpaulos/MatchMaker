<?php
	require 'mobile.php';
	echoDoctype();
?>

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<link type="text/css" rel="stylesheet" href="styles.css" />
	<title>User Input</title>
	<?php
		echoMeta();
	?>
</head>
<body>
	<div class="page">
		<h1 class="title">Match Maker</h1>
		
		<div class="content">
			<table style="width: 100%" border="1px">
				<?php
					//This page displays all of the data that is currently in the database
					//It is for testing purposes only and should not be placed in a public website
					
					require 'database.php';
					
					echo '<tr>
							<th>First Name</th>
							<th>Middle Name</th>
							<th>Last Name</th>
							<th>Gender</th>
							<th>Grade</th>';
					for($q = 0; $q < count($questions); ++$q){
						echo '<th>Q'.$q.'</th>';
					}
					echo '</tr>';
					
					$select = $db->prepare('SELECT * FROM '.$table);
					$select->execute();
					
					foreach($select as $row){
						echo '<tr>
							<td>'.$row['firstName'].'</td>
							<td>'.$row['middleName'].'</td>
							<td>'.$row['lastName'].'</td>
							<td>'.$row['gender'].'</td>
							<td>'.$row['grade'].'</td>';
						for($q = 0; $q < count($questions); ++$q){
							echo '<td>'.$row['q'.$q].'</td>';
						}
						echo '</tr>';
					}
				?>
			</table>
		</div>
	</div>
</body>
</html>