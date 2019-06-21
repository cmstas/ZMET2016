# get the latest scale1fbs.txt from CORE
echo "Getting latest scale1fbs.txt..."
echo "curl https://raw.githubusercontent.com/cmstas/CORE/master/Tools/datasetinfo/scale1fbs.txt > ../scale1fbs.txt"

curl https://raw.githubusercontent.com/cmstas/CORE/master/Tools/datasetinfo/scale1fbs.txt > ../scale1fbs.txt

#make the tarfile
tar -zcf package.tar.gz --exclude=*.tar.gz ../
