## COMPILER TEST SUITE

HTML=test/out/summary.html

LOGS=test/out/logs
mkdir -p $LOGS
rm -r $LOGS/*

chmod u+x test/makefile.sh

# =====================================================
# Begin tests
# =====================================================

echo "<html>" > $HTML
echo "<head>" >> $HTML
echo "<title>lscc: Compiler test suite</title>" >> $HTML
echo "</head>" >> $HTML
echo "<body>" >> $HTML

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

echo "<div>" >> $HTML
echo "<h2>make all</h2>" >> $HTML
echo "<pre style=\"white-space: pre-wrap;\">" >> $HTML
cat $LOGS/make_all.txt >> $HTML
echo "</pre>" >> $HTML
echo "</div>" >> $HTML

echo "Testing the lexer"
php test/lexer.php > $LOGS/lexer.txt 2>&1

echo "<div>" >> $HTML
echo "<h2>Lexer</h2>" >> $HTML
echo "<a href=\"logs/lexer.txt\">" >> $HTML
/dev/null | tail -1 $LOGS/lexer.txt >> $HTML
echo "</a>" >> $HTML
echo "</div>" >> $HTML

# =====================================================
# Parser
# =====================================================

echo "Testing the parser"

# =====================================================
# End tests
# =====================================================

echo "</body>" >> $HTML

echo "TEST COMPLETE"
echo "============="
echo "The test results are available at $HTML"
if type open > /dev/null; then
	open -a "Google Chrome" $HTML
fi
