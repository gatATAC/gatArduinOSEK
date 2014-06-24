echo "Led pair cycling $1"
pairnumber=$1
let led1=$[pairnumber*2]
led2=$[led1+1]

# Turn off first led
string="l"
string+=$led1
string+="0"
./i2cTest $string

# Turn off second led
string="l"
string+=$led2
string+="0"
./i2cTest $string

# Wait 2 seconds
sleep 2

# Turn green first led
string="l"
string+=$led1
string+="1"
./i2cTest $string

# Wait 1 second
sleep 1

# Turn green second led
string="l"
string+=$led2
string+="1"
./i2cTest $string

# Sleep for three seconds
sleep 3

# Turn red first led
string="l"
string+=$led1
string+="2"
./i2cTest $string

#Sleep for two seconds
sleep 2

# Turn red second led
string="l"
string+=$led2
string+="2"
./i2cTest $string


