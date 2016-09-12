NET=$(iwconfig wlp3s0 | grep -oP '(?<=ESSID:).[^\s]*')
TEMP=$(acpi -t | awk '{print $4}' | tr -d '.0')
MEM=$(free -m | awk '/Mem/ {print $3}')
TOTAL=$(free -m | awk '/Mem/ {print $2}')
BAT=$(acpi | awk '{print $4}' | tr -d '%,')
REM=$(acpi | awk '{print $5}')
DATE=$(date '+%A %d %B %H:%M:%S')
xsetroot -name "| NET: $NET | MEM: $MEM.$TOTAL | BAT: $BAT.$REM | $DATE "
