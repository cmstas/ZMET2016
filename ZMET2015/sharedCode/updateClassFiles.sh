pushd ../../Software/makeCMS3ClassFiles
root -l -b -q "makeCMS3ClassFiles(\"../../dilepbabymaker/unknown_test_80_data_ee.root\", \"t\", \"ZMET\", \"ZMet\", \"zmet\")"
mv ZMET.* ../../ZMET2015/sharedCode/
popd