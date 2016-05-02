#! /bin/bash

# export analysis_version="V00-00-17"
export analysis_version="V07-06-07"
echo "Analysis version = $analysis_version"
localdirectory=`pwd`

function link_output
{
	if [ ! -L "$localdirectory/output" ]; then
		echo "Linking to output directory: /nfs-7/userdata/ZMEToutput/output"
		ln -s /nfs-7/userdata/ZMEToutput/output
	else
		echo "Saving output to: /nfs-7/userdata/ZMEToutput/output"
	fi
}

function create_photon_output
{
	if [ ! -d $localdirectory/output/photon/$analysis_version ]; then
		echo "Creating directory, $localdirectory/output/photon/$analysis_version"
		mkdir -p $localdirectory/output/photon/$analysis_version
		sleep 1
	else
		echo "Saving photon output to $localdirectory/output/photon/$analysis_version"
		sleep 1
	fi
}

function create_analysis_output
{
	if [ ! -d $localdirectory/output/$analysis_version ]; then
		echo "Creating directory, $localdirectory/output/$analysis_version"
		mkdir $localdirectory/output/$analysis_version
		sleep 1
	else
		echo "Saving looper output to $localdirectory/output/$analysis_version"
		sleep 1
	fi
}

function create_plot_output
{
	if [ ! -d output/ZMET2015/$analysis_version/plots/Closure ]; then
		echo "Creating directory, output/ZMET2015/$analysis_version/plots/Closure"
		mkdir -p output/ZMET2015/$analysis_version/plots/Closure
		sleep 1
	else
		echo "Saving plots to output/ZMET2015/$analysis_version/plots/Closure"
		sleep 1
	fi

	if [ ! -e output/ZMET2015/$analysis_version/plots/Closure/index.php ]; then
		cp index.php output/ZMET2015/$analysis_version/plots/Closure/
	fi
}

function compile_looper
{
	echo "Compiling code."
	make -j5
	if [ ! "$?" -eq "0" ]; then
		echo "Code did not compile, exiting."
		exit
	fi
}

function make_gtemplates
{
	selection_region=$1
	iteration=$analysis_version
	sample=$2
	echo "running templateLooper."
	root -b -q "runPhotonTemplates.cc( \"$selection_region\", \"$iteration\", \"$sample\")"
}

function run_template_looper
{
	selection_region=$1
    iteration=$analysis_version
    sample_region=$2
	echo "running templateLooper."
	root -b -q "runTemplateLooper.cc( \"$selection_region\", \"$iteration\", \"$sample_region\")"
}


