<?php
require('inc/run_program.inc.php');
require('inc/c_tokens.inc.php');


$passed_num = 0;

for($test_num = 0; $test_num < 1000; $test_num++) {
	
	// generate random C tokens
	$tokens = array();
	$last_token_is_keyword = false;
	$last_token_is_number = false;
	$len = rand(0, 1000);
	for($i = 0; $i < $len; $i++) {
		switch(rand(0, 9)) {
			case 0: // keyword
				if($last_token_is_keyword || $last_token_is_number) {
					//$tokens[] = " ";
				}
				$tokens[] = $keywords[rand(0, sizeof($keywords)-1)];
				$last_token_is_keyword = true;
				$last_token_is_number = false;
				break;
			case 1: // assignment
				$last_token_is_keyword = false;
				$last_token_is_number = false;
				$tokens[] = $assignments[rand(0, sizeof($assignments)-1)];
				break;
			case 2: // binary operator
				$last_token_is_keyword = false;
				$last_token_is_number = false;
				$tokens[] = $binary_ops[rand(0, sizeof($binary_ops)-1)];
				break;
			case 3: // unary operator
				$last_token_is_keyword = false;
				$last_token_is_number = false;
				$tokens[] = $unary_ops[rand(0, sizeof($unary_ops)-1)];
				break;
			case 4: // punctuator
				$last_token_is_keyword = false;
				$last_token_is_number = false;
				$tokens[] = $punctuators[rand(0, sizeof($punctuators)-1)];
				break;
			case 5: // number
				if($last_token_is_keyword || $last_token_is_number) {
					//$tokens[] = " ";
				}
				$last_token_is_keyword = false;
				$last_token_is_number = true;
				$tokens[] = rand(0, 500);
				break;
			case 6: // string
				break;
				$last_token_is_keyword = false;
				$last_token_is_number = false;
				$tokens[] = random_c_string();
				break;
			case 7: // char
				$last_token_is_keyword = false;
				$last_token_is_number = false;
				$tokens[] = "'r'";
				break;
			case 18: // whitespace
				$last_token_is_keyword = false;
				$last_token_is_number = false;
				if(rand(0, 1)) $tokens[] = " ";
				else $tokens[] = "\n";
				break;
			case 9: // preprocessor lines
				$last_token_is_keyword = false;
				$last_token_is_number = false;
				$tokens[] = "\n# $i \"file$i.c\"\n";
				break;
		}
	}
	
	// construct the input
	$input = implode(' ', $tokens);
	
	// run the lexer
	$out = run_program('bin/c_lexer', $input);
	
	// parse the json
	$json = json_decode($out, true);
	
	
	// is the parsed array equivalent to the php-generated list?
	
	$src_i = 0;
	$out_i = 0;
	$passed = true;
	
	while($src_i < sizeof($tokens)) {
		$src_text = $tokens[$src_i];
		$out_text = $json[$out_i]["Text"];
		if($src_text === "\n" || $src_text === " " || strpos($src_text, '#') !== false) {
			$src_i++;
			continue;
		}
		
		//echo " " . $src_text . "  " . $out_text . "\n";
		
		if($src_text != $out_text) {
			echo "\nLexer does not match expected output:\n";
			echo "Expected " . $src_text . ", got " . $out_text . "\n";
			echo $tokens[$src_i-3] . '  ' . $json[$out_i-3]["Text"] . "\n";
			echo $tokens[$src_i-2] . '  ' . $json[$out_i-2]["Text"] . "\n";
			echo $tokens[$src_i-1] . '  ' . $json[$out_i-1]["Text"] . "\n";
			echo $tokens[$src_i] . '  ' . $json[$out_i]["Text"] . "\n";
			echo $tokens[$src_i+1] . '  ' . $json[$out_i+1]["Text"] . "\n";
			$passed = false;
			break;
		}
		
		$src_i++;
		$out_i++;
	}
	
	if($passed) {
		$passed_num++;
		echo "T" . $test_num . ":" . $src_i . "  ";
	} else {
		echo "T" . $test_num . " failed\n\n";
	}
}

echo "\n\nPASSED " . $passed_num . " TESTS\n";

?>
