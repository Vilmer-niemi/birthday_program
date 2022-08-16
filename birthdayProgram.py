from datetime import date
from pandas import set_option,DataFrame, read_csv
from os import getcwd
set_option('display.max_rows', None)
print(f"path: {getcwd()}/birthdays.csv")
df = read_csv(getcwd()+"/birthdays.csv")
today = date.today()

def days_between(Start:date, End:date, only_year:bool):
    if only_year:
        End = End.replace(year = date.today().year)
        Start = Start.replace(year = date.today().year)
        if (End-Start).days < 0:
            End = End.replace(year = date.today().year+1)
    return (End-Start).days

def getdays(dataframe:DataFrame):
    days = []
    for year, month, day in zip(dataframe["year"], dataframe["month"], dataframe["day"]):
        days.append(days_between(today,date(year,month,day),True))
    dataframe["days"] = days
    
def format(dataframe:DataFrame): 
    year_column = []
    month_column = []
    day_column = []
    for date in dataframe["birthday"]:
        if "/" in date: 
            day, month, year = map(int,date.split("/"))
        if "-" in date:
            year, month, day = map(int,date.split("-"))
        year_column.append(year)
        month_column.append(month)
        day_column.append(day)
    dataframe["year"], dataframe["month"], dataframe["day"] = year_column, month_column, day_column
    
#print(getBirthdays(False))
format(df)
getdays(df)
df = df.sort_values(by=["days"])
df = df.reindex(index=df.index[::-1])
print(df)
input()
