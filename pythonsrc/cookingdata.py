import random
import datetime
import pandas as pd


def Origins():
    Origin = ["A", "B", "C", "D", "E"]
    Number = 5
    return [i + str(j + 1) for i in Origin for j in range(Number)]


def DepTimes(Msdt):
    # Msdt = datetime.datetime(2020, 1, 1, 5, 0, 0)
    Medt = Msdt + datetime.timedelta(hours=5)
    Mstep = datetime.timedelta(minutes=15)

    result = []
    while Msdt < Medt:
        result.append(Msdt)
        Msdt += Mstep
    return result


Length = {"AB": 2, "AC": 2.25, "AD": 2.5, "AE": 2.75,
          "BC": 3, "BD": 3.5, "BE": 3.75, "BA": 2.1,
          "CD": 4, "CE": 4.25, "CA": 2.3, "CB": 2.95,
          "DE": 5, "DA": 2.4, "DB": 3.6, "DC": 4.15,
          "EA": 2.65, "EB": 3.8, "EC": 4.35, "ED": 5.1
          }


def Profit(length, Btype):
    if Btype == "T1":
        return length * 100 + 10 * random.uniform(0, 1)
    if Btype == "T2":
        return length * 150 + 10 * random.uniform(0, 1)


def PutEverything(Morning):
    Bustypes = ["T1", "T2"]
    origins = Origins()
    MorningRange = DepTimes(Morning)

    allrows = []
    for k in Bustypes:
        for i in origins:
            for j in origins:
                if i[0] != j[0]:
                    row = [i, j, k] # origin, destination, bustype
                    select_dep = random.randint(0, len(MorningRange) - 1)
                    row.append(MorningRange[select_dep])  # depdatetime

                    timeTaken = Length[i[0] + j[0]]

                    arrival = MorningRange[select_dep] + datetime.timedelta(hours=timeTaken) + \
                              datetime.timedelta(minutes=random.randint(0, 15))

                    row.append(arrival)

                    profit = Profit(timeTaken, k)
                    row.append(profit)
                    allrows.append(row)

    return allrows


def onedayData(day):
    Morning = day +datetime.timedelta(hours=5)
    morn = PutEverything(Morning)
    df1 = pd.DataFrame(morn, columns=['Origin', 'Destination', 'BusType', 'DepDateTime', 'ArrDateTime', 'Profit'])

    afternoon = day + datetime.timedelta(hours=13)
    morn = PutEverything(afternoon)
    df2 = pd.DataFrame(morn, columns=['Origin', 'Destination', 'BusType', 'DepDateTime', 'ArrDateTime', 'Profit'])

    evening = day + datetime.timedelta(hours=17)
    morn = PutEverything(evening)
    df3 = pd.DataFrame(morn, columns=['Origin', 'Destination', 'BusType', 'DepDateTime', 'ArrDateTime', 'Profit'])

    df = pd.concat([df1, df2, df3])

    return df



if __name__ == "__main__":
    day = datetime.datetime(2020, 1, 1, 0, 0)
    df = pd.DataFrame()
    for i in range(7):
        days = day + datetime.timedelta(days=i)
        dfi = onedayData(days)
        df = pd.concat([df, dfi])


    df.to_csv("../random_schedule7.csv")