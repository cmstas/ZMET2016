# Running and Drawing Limits for ZMET analysis

## Check out and compile Higgs Combine Tool (must be done once)

Make sure to do this from a clean environment, i.e. don't source any other setup scripts first.

``` bash
source setupLimits.sh
```

## Run the limits

Edit the file `doLimits.sh` to specify the scan you're running and the datacard location.
The limits are relatively fast to run (30-60 minutes for the longer scans) but best to run in a screen session.

From this directory, with a clean environment:
``` bash
screen
source /code/osgcode/cmssoft/cmsset_default.sh
cd CMSSW_7_1_5/src
cmsenv
cd ../..
source doLimits.sh
```

## Plot the results

The output of the command above will be a file with the limits stored as r-values, like `r-values_T5ZZ.root`.
To plot them in the standard CMS style, use the relevant script from this directory, i.e.
``` bash
root -b -q makeLimitHist_T5ZZ.C
```
