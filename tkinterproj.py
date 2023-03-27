# Python quiz using Tkinter with music player. A register/login feature incorporated to allow users
#   to take quiz. MySQL database used to store login data and questions/answers.

import hashlib
import random
from tkinter import *
import tkinter.filedialog as tk
import tkinter.messagebox as tk2
from tkinter import messagebox

import MySQLdb
import pygame

class Main:
    def __init__(self, master):
        self.master = master
        self.master.geometry("800x800+0+0")
        self.master.title("Online Quiz")
        self.master.config(bg="#009FBF")
        f = Frame(self.master, height=800, width=800, bg="azure", relief="ridge", bd=20)
        f.propagate(0)
        f.pack()

        self.mainTitle = Label(f, text="Python Quiz", fg="black" ,bg="azure",font=("Roman", 30, "bold")).place(x=300, y=300)
        self.register = Button(f, text="Register", width=20, height=3, fg="royalblue4", bg="lavender", font=("Roman", 10, "bold"), command=self.userRegister)
        self.login = Button(f, text="Login", width=20, height=3, fg="royalblue4", bg="lavender", font=("Roman", 10, "bold"), command=self.userLogin)
        self.music = Button(f, text="Listen to music", width=20, height=3, fg="royalblue4", bg="lavender", font=("Roman", 10, "bold"), command=self.userMusic)
        self.music.place(x=300, y=470)
        self.register.place(x=400, y=400)
        self.login.place(x=200, y=400)

    def userRegister(self):
        self.registerNew = Toplevel(self.master)
        self.registerNew.resizable(0, 0)
        self.registerNew = Register(self.registerNew)

    def userLogin(self):
        self.login = Toplevel(self.master)
        self.login.resizable(0, 0)
        self.login = Login(self.login)
    def userMusic(self):
        self.music = Toplevel(self.master)
        self.music.resizable(0, 0)
        self.music = Music(self.music)

listofSongs = []
class Music:
    def __init__(self, master):
        global musicGlobalVariable
        musicGlobalVariable = master
        self.master = master
        self.master.geometry("510x250+0+0")

        global f3
        f3=Frame(self.master, height=500, width=500, bg="azure", relief="ridge", bd=20)
        f3.grid(rowspan=5, columnspan=4)
        f3.propagate(0)

        self.playlistbox = Listbox(f3, width=40, height=10,selectmode=SINGLE)
        for song in listofSongs:
            f3.playlistbox.insert(END, song)
        self.playlistbox.grid(row=1)
        self.playButton = Button(f3, text='Play', command=self.play)
        self.addButton = Button(f3, text='Add', command=self.add)
        self.playButton.grid(row=4, column=0)
        self.addButton.grid(row=4, column=2)
        f3.pack()

        pygame.init()

    def play(self):
        if (len(listofSongs) == 0):
            tk2.showinfo('Notice', 'No songs in your playlist!\nPlease add songs.')
        else:
            pygame.mixer.music.stop()
            selectedSongs = self.playlistbox.curselection()
            global playlistbox
            playIt = listofSongs[int(selectedSongs[0])]
            pygame.mixer.music.load(playIt)
            pygame.mixer.music.play(0, 0.0)

    def add(self):
        file = tk.askopenfilenames(initialdir='C:/Users/babbu/Downloads')
        songsTuple = root.splitlist(file)
        songsList = list(songsTuple)
        for song in songsList:
            listofSongs.append(song);
            tempArray = song.split('/')
            songShort = tempArray[len(tempArray) - 1]
            self.playlistbox.insert(END, songShort)
class Login:
    def __init__(self, master):
        global loginGlobalVariable
        loginGlobalVariable = master
        self.master = master
        self.master.geometry("800x800+0+0")
        self.master.config(bg="azure")

        global frame2
        frame2 = Frame(self.master, height=800, width=800, bg="azure", relief="ridge", bd=20)
        frame2.propagate(0)
        frame2.pack()
        self.label = Label(frame2, text="User Login", bg="azure", font=("Times New Roman", 30))
        self.label1 = Label(frame2, text="Enter Username: ", bg="azure", font=("Times New Roman", 20))
        self.entry1 = Entry(frame2, width=30)
        self.label2 = Label(frame2, text="Enter Password: ", bg="azure", font=("Times New Roman", 20))
        self.entry2 = Entry(frame2, width=30, show="*")
        self.button1 = Button(frame2, text="Login", width=15, height=3, fg="royalblue4", bg="lavender", font=("Helvetica", 10, "bold italic"), command=self.buttonClick)
        self.button2 = Button(frame2, text="Cancel", width=15, height=3, fg="royalblue4", bg="lavender", font=("Helvetica", 10, "bold italic"), command=self.cancel)

        self.var = IntVar()
        self.checkB = Checkbutton(frame2, text='Show Password', bg="azure", fg="royalblue4", font=("Helvetica", 10, "bold italic"), variable=self.var, onvalue=1, offvalue=0, command=self.showPass)

        self.label.place(x=300, y=250)
        self.label1.place(x=150, y=350)
        self.entry1.place(x=300, y=350)
        self.label2.place(x=150, y=400)
        self.entry2.place(x=300, y=400)
        self.button1.place(x=250, y=500)
        self.button2.place(x=400, y=500)
        self.checkB.place(x=150, y=450)

    def showPass(self):
        if (self.var.get()):
            self.entry2.config(show="")
        else:
            self.entry2.config(show="*")

    def cancel(self):
        loginGlobalVariable.destroy()

    def buttonClick(self):
        conn = MySQLdb.connect(host='localhost', database='tkinterprojDB', user='root', password='SaDa2903!')
        cursor = conn.cursor()
        u = self.entry1.get()
        pw = self.entry2.get()
        self.entry1.delete(0, 200)
        self.entry2.delete(0, 200)
        p = hashlib.sha1((u[:5] + pw).encode('utf-8')).hexdigest()
        s = "select * from reg where uname='%s' and p='%s'"
        arg = (u, p)
        cursor.execute(s % arg)
        result = cursor.fetchall()
        if result:
            self.accWindow = Toplevel(loginGlobalVariable)
            self.accWindow.resizable(0, 0)
            self.acWin = userAccount(self.accWindow, u)
        else:
            messagebox.showerror("Error", "Invalid Username or Password, Try Again!")
            loginGlobalVariable.destroy()
        cursor.close()
        conn.close()

class Register:

    def __init__(self, master):
        global registerGlobalVariable
        registerGlobalVariable = master
        self.master = master
        self.master.geometry("800x800+0+0")
        self.master.title("Online Quiz - Registration")
        self.master.config(bg="azure")
        global f1
        f1 = Frame(self.master, height=800, width=800, bg="azure", relief="ridge", bd=20)
        f1.propagate(0)
        f1.pack()

        self.mainTitle = Label(f1, text="Register Yourself", bg="azure",font=("Helvetica", 30, "bold italic underline")).place(x=50, y=10)
        self.name = Label(f1, text="First Name : ", bg="azure", font=("Times New Roman", 10))
        self.lname = Label(f1, text="Last name : ", bg="azure", font=("Times New Roman", 10))
        self.email = Label(f1, text="Email id : ", bg="azure", font=("Times New Roman", 10))
        self.uname = Label(f1, text="Username :", bg="azure", font=("Times New Roman", 10))
        self.pw = Label(f1, text="Enter password : ", bg="azure", font=("Times New Roman", 10))

        self.var = IntVar()

        self.tname = Entry(f1, width=30)
        self.tlname = Entry(f1, width=30)
        self.temail = Entry(f1, width=30)
        self.tuname = Entry(f1, width=30)
        self.tpw = Entry(f1, width=30, show="*")

        self.submit = Button(f1, text="Submit", width=20, height=5, fg="royalblue4", bg="lavender",font=("Helvetica", 10, "bold italic"), command=self.submitMethod)
        self.cancel = Button(f1, text="Cancel", width=20, height=5, fg="royalblue4", bg="lavender",font=("Helvetica", 10, "bold italic"), command=self.c_cancel)

        self.checkB = Checkbutton(f1, text='Show Password', bg="azure", fg="royalblue4",font=("Helvetica", 10, "bold italic"), variable=self.var, onvalue=1,offvalue=0, command=self.showPassword)

        self.name.place(x=50, y=100)
        self.tname.place(x=200, y=100)
        self.lname.place(x=50, y=150)
        self.tlname.place(x=200, y=150)
        self.email.place(x=50, y=200)
        self.temail.place(x=200, y=200)
        self.uname.place(x=50, y=250)
        self.tuname.place(x=200, y=250)
        self.pw.place(x=50, y=300)
        self.tpw.place(x=200, y=300)
        self.submit.place(x=50, y=400)
        self.cancel.place(x=250, y=400)
        self.checkB.place(x=195, y=330)

    def showPassword(self):
        if (self.var.get()):
            self.tpw.config(show="")
        else:
            self.tpw.config(show="*")

    def check(self, l1):
        ht = 50
        f = 0
        s = 0
        for i in range(5):
            ht = ht + 50
            if len(l1[i]) == 0:
                self.l = Label(f1, text="! You cannot leave this empty", fg='red', bg="azure")
                self.l.place(x=400, y=ht)
            else:
                self.l = Label(f1, text="! You cannot leave this empty", bg="azure", fg="azure")
                self.l.place(x=400, y=ht)
                f = f + 1
        if l1[2].find("@") == -1 and l1[2].find(".") == -1 and len(l1[2]) != 0:
            self.l = Label(f1, text="! Please enter a valid email id", bg="azure", fg="red")
            self.l.place(x=400, y=200)
            s = 1
        else:
            if (len(l1[2]) > 0):
                self.l = Label(f1, text="! Please enter a valid email id", bg="azure", fg="azure")
                self.l.place(x=400, y=200)
        if len(l1[4]) < 8 and len(l1[4]) != 0:
            self.l = Label(f1, text="! Password must atleast have 8 characters", bg="azure", fg="red")
            self.l.place(x=400, y=300)
        else:
            if (len(l1[4]) > 0):
                self.l = Label(f1, text="! Password must atleast have 8 characters", bg="azure", fg="azure")
                self.l.place(x=400, y=300)
        if (f == 5 and len(l1[4]) >= 8 and s == 0):
            return 1
        else:
            return 0

    def submitMethod(self):
        conn = MySQLdb.connect(host='localhost', database='tkinterprojDB', user='root', password='SaDa2903!')
        cursor = conn.cursor()
        name = self.tname.get()
        lname = self.tlname.get()
        email = self.temail.get()
        uname = self.tuname.get()
        pw = self.tpw.get()
        p = hashlib.sha1((uname[:5] + pw).encode('utf-8')).hexdigest()
        l1 = [name, lname, email, uname, pw]
        c = self.check(l1)
        if c == 1:
            str = "select * from reg where uname='%s'"
            arg = (uname)
            cursor.execute(str % arg)
            row = cursor.fetchone()
            if row is not None:
                messagebox.showwarning("Error", "Username Already Taken, Try Again!")
                registerGlobalVariable.destroy()
            else:
                try:
                    s = "insert into reg(name,lname,email,uname,p,score) values('%s','%s','%s','%s','%s','%d')"
                    arg = (name, lname, email, uname, p, 0)
                    cursor.execute(s % arg)
                    conn.commit()
                    print("DEBUG: 1 ROW ADDED")
                    self.tname.delete(0, 'end')
                    self.tlname.delete(0, 'end')
                    self.temail.delete(0, 'end')
                    self.tuname.delete(0, 'end')
                    self.tpw.delete(0, 'end')
                    messagebox.showinfo("Success", "Registration Successful!")
                    registerGlobalVariable.destroy()
                except:
                    conn.rollback()
        cursor.close()
        conn.close()

    def c_cancel(self):
        registerGlobalVariable.destroy()

class userAccount:
    def __init__(self, master, u):
        global accountGlobalVariable
        self.u = u
        self.master = master
        accountGlobalVariable = master
        self.master.geometry("800x800+0+0")
        self.master.title("Welcome")
        self.master.config(bg="#009FBF")
        f3 = Frame(accountGlobalVariable, height=800, width=800, bg="azure", relief="ridge", bd=20)
        f3.propagate(0)
        f3.pack()
        conn = MySQLdb.connect(host='localhost', database='tkinterprojDB', user='root', password='SaDa2903!')
        cursor = conn.cursor()
        q = "select score from reg where uname='%s'"
        arg = (u)
        cursor.execute(q % arg)
        self.prevScore = cursor.fetchone()
        cursor.close()
        conn.close()
        self.greet = Label(f3, text="Welcome back, "+ u+"!", bg="azure",font=("Helvetica", 30, "bold")).place(x=220, y=270)
        self.lastScore = Label(f3, text="Last Score Achieved= " + str(self.prevScore[0]), bg="azure",font=("Helvetica", 20, "bold")).place(x=220, y=320)
        self.takeQuiz = Button(f3, text="Take Quiz", width=20, height=5, fg="royalblue4", bg="lavender", font=("Helvetica", 10, "bold italic"), command=self.access)
        self.takeQuiz.place(x=200, y=400)
        self.logout = Button(f3, text="Logout", width=20, height=5, fg="royalblue4", bg="lavender",font=("Helvetica", 10, "bold italic"), command=self.logout)
        self.logout.place(x=400, y=400)

    def access(self):
        self.quizWindow = Toplevel(self.master)
        self.quizWindow.resizable(0, 0)
        self.qw = Quiz(self.quizWindow, self.u)

    def logout(self):
        accountGlobalVariable.destroy()


class Quiz:
    def __init__(self, master, u):
        self.user = u
        global quizGlobalVariable
        quizGlobalVariable = master
        self.master = master
        self.master.geometry("1350x750+0+0")
        self.master.title("Online Quiz")
        self.master.config(bg="azure")
        global f1
        f = Frame(self.master, height=1080, width=1920, bg="azure", relief="ridge", bd=20)
        connection = MySQLdb.connect(host='localhost', database='tkinterprojDB', user='root', password='SaDa2903!')
        cursor = connection.cursor()

        global l1, answerstemp
        global questions
        questions = []
        global options
        options = []
        global answers
        answers = []
        answerstemp = []
        s1 = set()

        while len(s1) < 10:
            strQ = ""
            strA = ""
            id = random.randint(1, 10)
            s1.add(id)

        while len(s1) > 0:
            s = "select qstn from questions where QID=%d"
            id = s1.pop()
            arg = (id)
            cursor.execute(s % arg)
            strQ = strQ.join(list(cursor.fetchone()))
            questions.append(strQ)

            s = "select opA,opB,opC,opD from questions where QID=%d"
            arg = (id)
            cursor.execute(s % arg)
            options.append(list(cursor.fetchone()))

            s = "select ans from questions where QID=%d"
            arg = (id)
            cursor.execute(s % arg)
            l = list(cursor.fetchone())
            answerstemp.append(l)

        cursor.close()
        connection.close()
        l1 = {}
        for i in range(10):
            l1[i] = 0

        f.propagate(0)
        f.pack()
        self.qno = 0
        self.score1 = 0
        self.ques = self.create_q(f, self.qno)
        self.opts = self.create_options(f)
        self.display_q(self.qno)
        self.Back = Button(f, text="<- Back", width=15, height=3, fg="royalblue4", bg="snow2",font=("Helvetica", 10, "bold italic"), command=self.back).place(x=100, y=325)
        self.Next = Button(f, text="Next ->", width=15, height=3, fg="royalblue4", bg="snow2",font=("Helvetica", 10, "bold italic"), command=self.next).place(x=250, y=325)
        self.submit = Button(f, text="Submit", width=34, height=2, fg="ghost white", bg="DeepSkyBlue2",font=("Helvetica", 10, "bold italic"), command=self.Submit).place(x=100, y=400)

    def create_q(self, master, qno):
        qLabel = Label(master, text=questions[qno], bg='azure', font=("Times New Roman", 20))
        qLabel.place(x=30, y=70)
        return qLabel

    def create_options(self, master):
        b_val = 0
        b = []
        ht = 85
        self.opt_selected = IntVar()
        while b_val < 4:
            btn = Radiobutton(master, text="", variable=self.opt_selected, value=b_val + 1, bg='azure',
                              font=("Times New Roman", 20))
            b.append(btn)
            ht = ht + 40
            btn.place(x=30, y=ht)
            b_val = b_val + 1
        return b

    def display_q(self, qno):
        b_val = 0
        self.ques['text'] = str(qno + 1) + ". " + questions[qno]
        for op in options[qno]:
            self.opts[b_val]['text'] = op
            b_val = b_val + 1

    def next(self):
        self.qno += 1

        if self.qno >= len(questions):
            self.qno -= 1
            messagebox.showwarning("Warning", "Finished! Press Submit to proceed")
        else:
            l1[self.qno - 1] = self.opt_selected.get()
            self.opt_selected.set(l1[(self.qno)])
            self.display_q(self.qno)

    def back(self):
        l1[self.qno] = self.opt_selected.get()
        self.qno -= 1
        if self.qno < 0:
            self.qno += 1
            messagebox.showerror("Error", "You are already in the start!!!")
        else:
            self.display_q(self.qno)
            c = l1[self.qno]
            self.opt_selected.set(c)

    def Submit(self):
        l1[self.qno] = self.opt_selected.get()
        x = 0
        y = True
        for i in range(10):
            if (l1[i] == 0):
                x += 1
        if (x > 0 and x != 1):
            y = messagebox.askyesno("Warning", "You have not attempted " + str(x) + " questions, Are you sure you want to submit?, You won't be able to make changes again")
        elif (x == 1):
            y = messagebox.askyesno("Warning", "You have not attempted " + str(x) + " question, Are you sure you want to submit?, You won't be able to make changes again")
        if (y == True or x == 0):
            s = 0
            for i in range(10):
                if (l1[i] == answerstemp[i][0]):
                    s = s + 1

        conn = MySQLdb.connect(host='localhost', database='tkinterprojDB', user='root', password='SaDa2903!')
        cursor = conn.cursor()
        q = "update reg set score='%d' where uname= '%s'"
        arg = (s, self.user)
        cursor.execute(q % arg)
        conn.commit()
        cursor.close()
        conn.close()

        messagebox.showinfo("Result", "Your Score is: " + str(s) + "/10")
        quizGlobalVariable.destroy()
root=Tk()
RegObj = Main(root)
root.mainloop()