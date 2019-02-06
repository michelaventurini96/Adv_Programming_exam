#!/usr/bin/python

from datetime import datetime

class PostcardList:
    def __init__(self):
        self._file = ""
        self._postcards = [] #list
        self._date  = {} #dict
        self._from = {} #dict
        self._to = {} #dict

    #create the list _postcards and the dictionaries _date, _from and _to
    #reading from the file_name (passed as argument)
    def readFile(self,file_name):
        try:
            self._file=file_name
            f = open(self._file, "r")
            file_content = f.readlines()
            f.close()
            for i in range(0,len(file_content)):
                self._postcards.append(file_content[i])
            self.parsePostcards()
        except:
            print ("This file doesn't exist")

    def getNumberOfPostcards (self):
        return len(self._postcards)

    #Given one postcard insert the data into the dictionaries
    def parsePostcards(self):
        for i in range (0,len(self._postcards)):
            c = self._postcards[i]
            c = c.split(" ")
            date = (c[0].lstrip("date:")).replace(";","")
            sender = c[1].lstrip("from:").replace(";","")
            rec = c[2].lstrip("to:").replace(";\n","")
            date = datetime.strptime(date, "%Y-%m-%d")
            #temp = datetime.datetime.strptime(data,'%Y-%m-%d');
            if date not in self._date:
                self._date[date]=[]
            self._date[date].append(i)
            if sender not in self._from:
                self._from[sender]=[]
            self._from[sender].append(i)
            if rec not in self._to:
                self._to[rec]=[]
            self._to[rec].append(i)
            #
            #
            #
            # self._date[temp.date()]=i
            # self._from[sender]=i
            # self._to[rec]=i

    #write the postcards into the file_name (passed as argument)
    def writeFile(self,file_name):
        self._file=file_name
        if not self._postcards:
            print("No postcards to write")
        f = open(self._file,"w+");
        for i in range(0, len(self._postcards)):
            f.write(self._postcards[i])
        f.close()

    def updateFile(self,file_name):
        # if not self._postcards:
        #     print("No postcards to write")
        f = open(self._file,"a");
        for i in range(0, len(self._postcards)):
            f.write(self._postcards[i])
        f.close()

    def updateLists(self,file_name):
        try:
            self._file=file_name
            f = open(self._file, "r")
            file_content = f.readlines()
            f.close()
            for i in range(0,len(file_content)):
                self._postcards.append(file_content[i])
            self.parsePostcards();
        except:
            print ("This file doesn't exist")

    def getPostcardsBySender(self, sender):
        postBySender = []
        if sender in self._from:
            for i in self._from[sender]:
                postBySender.append(self._postcards[i])
        return postBySender

    def getPostcardsByReceiver(self, receiver):
        postByReceiver = []
        if receiver in self._to:
            for i in self._to[receiver]:
                postByReceiver.append(self._postcards[i])
        return postByReceiver

    def getPostcardsByDateRange(self,date_range):
        postDate = []
        for i in self._date:
            if date_range[0] <= i <= date_range[1]:
                for j in self._date[i]:
                    postDate.append(self._postcards[j])
        return postDate
