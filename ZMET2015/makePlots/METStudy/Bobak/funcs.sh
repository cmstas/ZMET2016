function makePuWeight {
	sed -e 's,^  TCut weight = "evt_scale1fb\*2\.3";$,  //TCut weight = "evt_scale1fb\*2\.3";,g' -e 's,^  //TCut weight = "evt_scale1fb\*2\.3\*puWeight";$,  TCut weight = "evt_scale1fb\*2\.3\*puWeight";,g' < METStudy_all.cc > METStudy_all_puWeight.cc

	cp METStudy_all.cc METStudy_all.bak
	mv METStudy_all_puWeight.cc METStudy_all.cc
}

function makeUnweighted {
	sed -e 's,^  //TCut weight = "evt_scale1fb\*2\.3";$,  TCut weight = "evt_scale1fb\*2\.3";,g' -e 's,^  TCut weight = "evt_scale1fb\*2\.3\*puWeight";$,  //TCut weight = "evt_scale1fb\*2\.3\*puWeight";,g' < METStudy_all.cc > METStudy_all_puWeight.cc

	cp METStudy_all.cc METStudy_all.bak
	mv METStudy_all_puWeight.cc METStudy_all.cc
}


function runTest {
	makePuWeight
	root -l -b -q METStudy_all.cc
	makeUnweighted
	root -l -b -q METStudy_all.cc
}

function waitForMerge {
	while [ 1 ]
	do
		a=`ps aux | grep cwelke | grep "root -b -q mergeHadoopFiles.C"`
		if [[ -z $a ]]
		then
			break
		else
			echo "Still waiting at " `date`
		fi
		sleep 60
	done

	runTest
}