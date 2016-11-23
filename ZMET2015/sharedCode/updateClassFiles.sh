pushd ../../Software/makeCMS3ClassFiles
root -l -b -q "makeCMS3ClassFiles.C(\"../../dilepbabymaker/unknown_test_80_Wgamma_withW_P.root\", \"t\", \"ZMET\", \"ZMet\", \"zmet\")"
mv ZMET.* ../../ZMET2015/sharedCode/
popd
