#! /bin/bash

function drawtemplates
{
	region=$1	
	isbad=""
	if [ ! -d ../output/ZMET2015/V00-00-20/plots/Templates/${region}${isbad} ]; then
		mkdir ../output/ZMET2015/V00-00-20/plots/Templates/${region}${isbad}	
	fi
	cp ../output/ZMET2015/index.php ../output/ZMET2015/V00-00-20/plots/Templates/${region}${isbad}/
	rm ../output/ZMET2015/V00-00-20/plots/Templates/${region}${isbad}/*.png
	root -b -q "plotPhotonTemplates.cc+(\"${region}\")"
}

drawtemplates "2jets_edgec"
drawtemplates "2jets_edgef"
drawtemplates "3jets_edgec"
drawtemplates "3jets_edgef"
drawtemplates "2jets_edgec_bad"
drawtemplates "2jets_edgef_bad"
drawtemplates "3jets_edgec_bad"
drawtemplates "3jets_edgef_bad"
