syslog_path = 'syslog.6.txt'

import collections
import re

unified_log = collections.defaultdict(list)

# syslog

#invalid_pulse = re.compile('Feb (\d+) (\d+:\d+:\d+) emonpi emon-pwr1\[\d+\]: (Detected .*)')
invalid_pulse = re.compile('Feb (\d+) (\d+:\d+:\d+) emonpi emon-pwr1\[\d+\]: Detected invalid pulse \(length=(\d+) ms\)')

for line in open(syslog_path):
    match = invalid_pulse.match(line)
    if match:
        day = int(match.group(1))
        time = match.group(2)
        message = match.group(3)
        unified_log[(day, time)].append(message)

# emon-cms data

dump_file_path = 'emoncms-dump.txt'

data_entry = re.compile('(\d+)/\d+/\d+ (\d+)\.(\d+)\.(\d+) (\d+)')

for line in open(dump_file_path):
    match = data_entry.match(line)
    if match:
        day = int(match.group(1))
        time = '{}:{}:{}'.format(int(match.group(2)) + 1, match.group(3), match.group(4))
        power = int(match.group(5))
        if power < 1000:
            message = '{} -- LOW POWER!'.format(power)
        else:
            message = str(power)
#        unified_log[(day, time)].append(message)

for k in sorted(unified_log.keys()):
    day, time = k
    for message in unified_log[k]:
        print day, time, message
