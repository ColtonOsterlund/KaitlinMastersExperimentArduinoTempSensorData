import schedule
import os
import sys
 
def uploadGithub():
	os.system("git add .")
	os.system("git commit -m "updating temperature data file"")
	os.system("git push origin master")

schedule.every(3600).seconds.do(uploadGithub)
while True:
	try:
		schedule.run_pending()
		time.sleep(1)
	except Exception as e:
		print(e)
		print("\nexception - restarting\n")
		ser.close()
		os.system("python uploadGithub.py")
		sys.exit()