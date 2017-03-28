## COMPILER TEST SUITE

HTML=test/out/summary.html

LOGS=test/out/logs
mkdir -p $LOGS
rm -r $LOGS/*

chmod u+x test/makefile.sh

if [[ "$1" == "clean" ]]; then
	echo "Cleaning output directory..."
	rm -rf test/out/asm
	rm -rf test/out/unit
	rm -rf $LOGS
	rm -f test/out/makefile_dependencies.png
	rm -f test/out/summary.html
	echo "Done :)"
	exit
fi

# =====================================================
# Begin tests
# =====================================================
echo "lssc: Compiler test suite"
echo "========================="

echo "<html>" > $HTML
echo "<head>" >> $HTML
echo "<title>lscc: Compiler test suite</title>" >> $HTML
echo "<style>" >> $HTML
echo "h2 { margin-top: 60px; }" >> $HTML
echo ".pass { color: darkGreen; }" >> $HTML
echo ".fail { color: pink; background-color: darkRed; }" >> $HTML
echo "</style>" >> $HTML
echo "</head>" >> $HTML
echo "<body>" >> $HTML
echo "<h1>lssc: Compiler test suite</h1>" >> $HTML

# =====================================================
# Makefile
# =====================================================

echo "Testing makefile dependencies"
test/makefile.sh > $LOGS/makefile.txt 2>&1

echo "<div>" >> $HTML
echo "<h2>Makefile dependencies</h2>" >> $HTML
echo "<a href=\"makefile_dependencies.png\"><img src=\"makefile_dependencies.png\" width=\"100%\" /></a>" >> $HTML
echo "</div>" >> $HTML

# =====================================================
# Lexer
# =====================================================

echo "Performing a make clean"
echo "# make clean" > $LOGS/make_all.txt 2>&1
make clean >> $LOGS/make_all.txt 2>&1
echo "Performing a make all"
echo "# make all" >> $LOGS/make_all.txt 2>&1
make all >> $LOGS/make_all.txt 2>&1
PASS=$?

echo "<div>" >> $HTML
if [[ $PASS -eq 0 ]]; then
	echo "<h2 class=\"pass\">make all</h2>" >> $HTML
else
	echo "<h2 class=\"fail\">make all</h2>" >> $HTML
fi
echo "<pre style=\"white-space: pre-wrap;\">" >> $HTML
cat $LOGS/make_all.txt >> $HTML
echo "</pre>" >> $HTML
echo "</div>" >> $HTML

echo "Testing the lexer"
php test/lexer.php > $LOGS/lexer.txt 2>&1
PASS=$?

echo "<div>" >> $HTML
if [[ $PASS -eq 0 ]]; then
	echo "<h2 class=\"pass\">Lexer</h2>" >> $HTML
else
	echo "<h2 class=\"fail\">Lexer</h2>" >> $HTML
fi
echo "<a href=\"logs/lexer.txt\">" >> $HTML
tail -1 $LOGS/lexer.txt >> $HTML
echo "</a>" >> $HTML
echo "</div>" >> $HTML

# =====================================================
# Unit tests check on gcc
# =====================================================

echo "Running automated unit tests against GCC golden reference"
test/unit.sh gcc > $LOGS/unit_gcc.txt 2>&1
PASS=$?

echo "<div>" >> $HTML
if [[ $PASS -eq 0 ]]; then
	echo "<h2 class=\"pass\">Unit tests on gcc</h2>" >> $HTML
else
	echo "<h2 class=\"fail\">Unit tests on gcc</h2>" >> $HTML
fi
echo "<a href=\"logs/unit_gcc.txt\">" >> $HTML
tail -1 $LOGS/unit_gcc.txt >> $HTML
echo "</a>" >> $HTML
echo "</div>" >> $HTML

# =====================================================
# Unit tests
# =====================================================

echo "Running automated unit tests on lscc"
test/unit.sh > $LOGS/unit.txt 2>&1
PASS=$?

echo "<div>" >> $HTML
if [[ $PASS -eq 0 ]]; then
	echo "<h2 class=\"pass\">Unit tests on lscc</h2>" >> $HTML
else
	echo "<h2 class=\"fail\">Unit tests on lscc</h2>" >> $HTML
fi
echo "<a href=\"logs/unit.txt\">" >> $HTML
echo "View raw logs here" >> $HTML
echo "</a>" >> $HTML
echo "<pre style=\"white-space: pre-wrap;\">" >> $HTML
cat $LOGS/unit.txt >> $HTML
echo "</pre>" >> $HTML
echo "</div>" >> $HTML

# =====================================================
# End tests
# =====================================================

echo "</body>" >> $HTML

echo
echo "TEST COMPLETE"
echo "============="
echo "The test results are available at $HTML"
#if type open > /dev/null; then
#	open -a "Google Chrome" $HTML
#fi
