


from CommandHandler import CommandHandler
import time

if __name__=="__main__":
    ch = CommandHandler()
    while True:
         done,out = ch.execute("python3 main.py")
         if done:
             print(out)
         time.sleep(10)