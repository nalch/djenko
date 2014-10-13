import argparse
import json
import urllib2
import time

import serial



# Arduino Configuration
SUCCESS = 'g'
FAILURE = 'r'
BUILDING = 'a'
UNSTABLE = 'y'
ERROR = 'e'


# parse commandline
parser = argparse.ArgumentParser()
parser.add_argument('jenkins_job', help="the job's name")
parser.add_argument('-v', '--verbose', help='print debug messages to the console', action='store_true', default=False)
parser.add_argument('-u', '--jenkins_url', help="jenkin's url. Default: http://localhost:8080", default='http://localhost:8080')
parser.add_argument('-i', '--fetch_interval', help="interval to fetch the job's status in seconds. Default: 30", type=int, default=30)
parser.add_argument('-p', '--serial_port', help="the hardware device's serial port. Default: /dev/ttyUSB0", default='/dev/ttyUSB0')
args = parser.parse_args()

if not args.jenkins_url.endswith('/'):
    args.jenkins_url += '/'

if args.verbose:
    print(args)


def get_status(job_name):
    """ calls the jenkinsapi for the json representation of the job's last build and returns the timestamp and result
    """
    try:
        jenkins_streams = urllib2.urlopen(args.jenkins_url + 'job/' + job_name + '/lastBuild/api/json')
    except urllib2.HTTPError as e:
        print 'URL Error: ' + str(e.code)
        print 'job name [' + job_name + '] probably wrong)'

    try:
        build_status_json = json.load(jenkins_streams)
    except:
        print 'Failed to parse json'

    return job_name, build_status_json['timestamp'], build_status_json['result'],



# Configurations
ser = serial.Serial(args.serial_port, 9600)

# start processing loop
while 1:

    # dirty "catch-all-exceptions-without-exiting-program"-try
    try:

        status = get_status(args.jenkins_job)

        if args.verbose:
            print args.jenkins_job, status[2]

        # process jobstates
        if status[2] == "UNSTABLE":
            ser.write(UNSTABLE)
        elif status[2] == "SUCCESS":
            ser.write(SUCCESS)
        elif status[2] == "FAILURE":
            ser.write(FAILURE)
        elif status[2] == "ABORTED":
            ser.write(FAILURE)
        elif status[2] == 'ERROR':
            ser.write(ERROR)
        elif status[2] is None:
            ser.write(BUILDING)

    except Exception as e:
        ser.write(ERROR)
        print e

    time.sleep(args.fetch_interval)