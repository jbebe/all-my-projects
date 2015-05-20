#!/usr/bin/python2.7
#email
import smtplib
from email.mime.text import MIMEText
#commandline
from subprocess import Popen, PIPE
from os import devnull
#ssh
from Exscript.protocols import SSH2
from Exscript import Account
#regex
import re
#psql api
import psycopg2
#basic
from sets import Set
from time import sleep

psqlSet = Set()
aliveSet = Set()
badGuys = Set()

def getPSQL():
	conn = psycopg2.connect("dbname=****** user=****** host=127.0.0.1 password=******")
	cur = conn.cursor()
	#select query
	cur.execute("SELECT * FROM ****** where ****** << '******' or ****** << '******'")
	#fetch selection
	allEntry = cur.fetchall()
	[psqlSet.add(entry[0]) for entry in allEntry]
	return

def getArp():
	account = Account('show', 'show')
	conn = SSH2()
	conn.connect('rtr-1')
	conn.login(account)	
	conn.execute('terminal length 0')
	conn.execute('show ip arp | exclude Incomplete')
	ipPattern = re.compile('(******)')
	
	for line in conn.response.split('\n'):
		m = ipPattern.search(line)
		if m:
			aliveSet.add(m.group(1))
 
	conn.send('exit')
	conn.close()
	return

def ping(network, mask):
	ping_handle = Popen(['fping', '-c 2', '-A', '-g', network+'/'+mask], stdout=PIPE, stderr=PIPE)
	ping_handle.communicate()
	#csak a biztonsag kedveert
	return

def sendMail(recipient, subject, body):
	sender = "ip_checker@sch.bme.hu"

	mailHandle = MIMEText(body)
	mail['Subject'] = subject
	mail['From'] = sender
	mail['To'] = recipient

	s = smtplib.SMTP('localhost')
	s.sendmail(sender, recipient, mail.as_string())
	s.quit()
	return

def findDiff():
	ping('******','******')
	ping('******','******')
	#nem kene ide egy sleep?
	sleep(50/1000)
	getArp()
	getPSQL()
	diffNotDB = aliveSet.difference(psqlSet)
	diffNotAlive = psqlSet.difference(aliveSet)
	
	#alive ips not in DB
	#print("Alive ips not in DB (size: %d)" % len(diffNotDB))
	for entry in diffNotDB:
		if entry not in badGuys:
			sendMail("megfelelo szemely", "Not in DB", "")
			badGuys.add(entry)
		#print(entry)
	#DB records that are not alive
	"""
	print("DB records (not alive) (size: %d)" % len(diffNotAlive))
	for entry in diffNotAlive:
		print(entry)
	"""
	return

findDiff()
