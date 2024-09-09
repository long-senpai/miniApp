import websocket
from threading import Thread
from bokeh.layouts import column
from bokeh.models import Div
from bokeh.plotting import curdoc
from bokeh.io import output_notebook
from bokeh.driving import linear

# Output in notebook (if running in Jupyter Notebook)
output_notebook()


# This function updates the number in the Div every time it's called
counter = 0
recv_message = 0

# Create a Div widget to display a number
number_display = Div(text="<h1 style='text-align:center;'>0</h1>", width=200, height=100)

def websocket_reader():
    ws = websocket.WebSocket()
    ws.connect("ws://localhost:8080")
    global recv_message
    while True:
        try:
            message = ws.recv()  # Blocking call to get message
            recv_message = int(message)
        except Exception as e:
            print(f"Error in WebSocket connection: {e}")
            break

ws_thread = Thread(target=websocket_reader)
ws_thread.start()



@linear()
def update(step):
    global recv_message
    number_display.text = f"<h1 style='text-align:center;'>{recv_message}</h1>"

# Add the number display to the document
curdoc().add_root(column(number_display))

# Update the number every 500 milliseconds
curdoc().add_periodic_callback(update, 1)
