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


# parse commandline
parser = argparse.ArgumentParser()
parser.add_argument('jenkins_job', help="the to be monitored job's name")
parser.add_argument('-v', '--verbose', help='prints debug messages to the console', action='store_true', default=False)
parser.add_argument('-u', '--jenkins_url', help='', default='http://localhost:8080/job/')
parser.add_argument('-i', '--fetch_interval', help='interval to call the jenkins status in seconds', type=int, default=5)
parser.add_argument('-p', '--serial_port', help="the hardware device's serial port", default='/dev/ttyUSB0')
args = parser.parse_args()

print(args)


def get_status(job_name):
    """ calls the jenkinsapi for the json representation of the job's last build and returns the timestamp and result
    """
    try:
        jenkins_streams = urllib2.urlopen(args.jenkins_url + job_name + '/lastBuild/api/json')
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
        elif status[2] is None:
            ser.write(BUILDING)

    except Exception as e:
        print e

    time.sleep(args.fetch_interval)
