
from flask import Flask

app = Flask(__name__)

@app.route('/')
def base():
  return 'Flask Server'

@app.route('/get', methods=['GET'])
def handle_get():
  return 'GET request recieved'

if __name__ == '__main__':
  app.run(host="0.0.0.0", port=5000)