echo "running command from" $PWD
cd $PWD
git add .
echo "Enter commit message:"
read message
git commit -am "$message"
git push