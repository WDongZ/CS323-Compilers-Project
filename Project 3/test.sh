for i in {1..9}; do
    echo "========================"
    echo "Running test case: test_3_r$i"
    ./a ./testcase/test_3_r$i.spl
    echo "========================"
    echo ""
done
