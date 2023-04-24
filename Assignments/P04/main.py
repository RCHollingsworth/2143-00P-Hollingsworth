from dice import Die
from dice import Dice
from random import shuffle
from rich import print
import sys

if __name__ == '__main__':
  print("Please Enter the Number of Dice You Want to Roll Followed by the Number of Sides Each Dice has. In the Format 1d2, the First Number Being the Number of Dice and the Second Number Being the Number of Sides.")
  i = str(input())
  cin = i.split("d")
  first = int(cin[0])
  second = int(cin[1])
  d1 = Dice(second, first)
  print("How Many Times Do You Want to Roll the Dice:")
  cin2 = int(input())
  d1.rolling(cin2, first)