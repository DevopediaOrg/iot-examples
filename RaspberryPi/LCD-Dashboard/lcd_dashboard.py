'''=====================================================================
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  ---------------------------------------------------------------------
  Purpose : We use tkinter package to display a GUI window on a 3.5"
            480x320 LCD display from Waveshare.
            App shows current time, Devopedia logo, and the latest
            tech news. News is pulled via a free REST API service and 
            it's use requires an API key. The key is expected to be
            defined in an environment variable NEWS_API_KEY.
  Date    : 16 Apr 2019
  Boards  : Raspberry Pi 2, 3
  =====================================================================
'''

import os
import time
import tkinter as tk
import tkinter.font as tkFont
import requests
         

#===============================================================
# Inits
#---------------------------------------------------------------
val_time = None
val_news = None
news_titles = []


#===============================================================
# Functions
#---------------------------------------------------------------
def read_news(then=0):
    # Call the API once every 20 mins
    now = time.time()
    if now - then < 20*60:
      return None

    url = ('https://newsapi.org/v2/top-headlines?'
          'category=technology&'
          'language=en&'
          'apiKey={}'.format(os.environ['NEWS_API_KEY']))
    response = requests.get(url)
    if response.status_code == 200:
        titles = set(item['title'] for item in response.json()['articles'])
        then = now
        return (titles, then)


def update_news(root, val_news, titles, iter_title=None, then=0):
    recents = read_news(then)
    if recents:
        titles, iter_title, then = recents[0], iter(recents[0]), recents[1]

    try:
        title = next(iter_title)
    except StopIteration:
        iter_title = iter(titles)
        title = next(iter_title)
    if len(title) > 80: title = title[:79] + '…'
    val_news.set(title)

    root.after(5000, update_news, root, val_news, titles, iter_title, then)


def update_time(root, val_time):
    val_time.set(time.strftime("%H:%M",time.localtime()))
    root.after(1000, update_time, root, val_time)


#===============================================================
# Main processing
#---------------------------------------------------------------
# Create the main window
root = tk.Tk()
root.title("LCD Dashboard Example")
root.config(cursor="none")
root.attributes('-fullscreen', True)

# Create the main container, use pack manager to layout and expand to fit window
frame = tk.Frame(root, bg='black')
frame.pack(fill=tk.BOTH, expand=1)

val_time = tk.StringVar()
val_news = tk.StringVar()
ft_time = tkFont.Font(family='Courier New', size=-48)
ft_news = tkFont.Font(size=-30)

# Create widgets
wg_time = tk.Label(frame, textvariable=val_time, font=ft_time, fg='red', bg='black')
wg_news = tk.Label(frame, textvariable=val_news, font=ft_news, wraplength=240, fg='yellow', bg='black')
logo = tk.PhotoImage(master=frame, file="devopedia.logo.png")
wg_logo = tk.Label(frame, image=logo, bg='black')

# Layout widgets in a grid in the frame
wg_time.grid(row=0, column=0, padx=20, pady=0)
wg_logo.grid(row=1, column=0, padx=20, pady=0)
wg_news.grid(row=0, column=1, rowspan=2, ipadx=20, padx=0, pady=0)

# Let the grid cells fill the display window
frame.rowconfigure(0, weight=2)
frame.rowconfigure(1, weight=1)
frame.columnconfigure(0, weight=1)
frame.columnconfigure(1, weight=2)

# Start and update first views
root.after(20, update_time, root, val_time)
root.after(50, update_news, root, val_news, news_titles)
root.mainloop()
