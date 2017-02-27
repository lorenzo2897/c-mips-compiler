<?php
	$keywords = array(
		"auto",
		"break",
		"case",
		"char",
		"const",
		"continue",
		"default",
		"do",
		"double",
		"else",
		"enum",
		"extern",
		"float",
		"for",
		"goto",
		"if",
		"int",
		"long",
		"register",
		"return",
		"short",
		"signed",
		"sizeof",
		"static",
		"struct",
		"switch",
		"typedef",
		"union",
		"unsigned",
		"void",
		"volatile",
		"while"
	);
	
	$assignments = array(
		">>=",
		"<<=",
		"+=",
		"-=",
		"*=",
		"/=",
		"%=",
		"&=",
		"^=",
		"|=",
		"="
	);
	
	$binary_ops = array(
		">>",
		"<<",
		"&&",
		"||",
		"<=",
		">=",
		"==",
		"!=",
		"-",
		"+",
		"*",
		"/",
		"%",
		"<",
		">",
		"^",
		"|"
	);
	
	$unary_ops = array(
		"++",
		"--",
		"&",
		"!",
		"~"
	);
	
	$punctuators = array(
		"...",
		
		"->",
		".",
		
		";",
		"{",
		"}",
		",",
		":",
		"?",
		"(",
		")",
		"[",
		"]"
	);
	
	$str_pick = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@$%^&*()-_=+[]{}|;:<>,./?";
	$str_pick_len = strlen($str_pick);
	$str_escaped = array(
		'\\n', '\\r', '\\t', '\\\\', '\\"', '\\\'', '\\0'
	);
	$str_escaped_len = sizeof($str_escaped);
	
	
	function random_c_string() {
		global $str_pick, $str_pick_len, $str_escaped, $str_escaped_len;
		
		$str = "";
		$len = rand(0, 16);
		for($i = 0; $i < $len; $i++) {
			$char = rand(0, $str_pick_len + 10);
			if($char < $str_pick_len) {
				$str .= $str_pick[$char];
			} else {
				$str .= $str_escaped[$char % $str_escaped_len];
			}
		}
		
		return '"' . $str . '"';
	}
?>




