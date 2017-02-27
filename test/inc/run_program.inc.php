<?php
		
function run_program($path, $stdin) {
	$descriptorspec = array(
		0 => array("pipe", "r"),  // stdin is a pipe that the child will read from
		1 => array("pipe", "w"),  // stdout is a pipe that the child will write to
		2 => array("pipe", "w") // stderr is a file to write to
	);
	
	$cwd = NULL;
	$env = array();
	
	$process = proc_open($path, $descriptorspec, $pipes, $cwd, $env);
	
	if (is_resource($process)) {
		// $pipes now looks like this:
		// 0 => writeable handle connected to child stdin
		// 1 => readable handle connected to child stdout
		// 2 => readable handle connected to child stderr
		
		fwrite($pipes[0], $stdin);
		fclose($pipes[0]);
		
		$stdout = stream_get_contents($pipes[1]);
		fclose($pipes[1]);
		
		$stderr = stream_get_contents($pipes[2]);
		fclose($pipes[2]);
		
		// It is important that you close any pipes before calling
		// proc_close in order to avoid a deadlock
		$return_value = proc_close($process);
	
		// output
		if($res != "") {
			echo "===== stderr: =====\n";
			echo $stderr;
		}
		if($return_value) echo "\nProgram exited with return value $return_value!\n";
		
		return $stdout;
	} else {
		echo "Program failed to run.\n";
		return "";
	}
}

?>