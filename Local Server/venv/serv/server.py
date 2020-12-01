from flask import Flask, request
 
app = Flask(__name__)
 
@app.route('/post', methods = ["POST"])
def post():
    print(request.authorization["username"])
    print(request.authorization["password"])
    print(request.data) 
    
    print (request.is_json)
    content = request.get_json()
    print (content)
    print ("machineID = ", content['machineID'])
    print ("destination = ", content["destination"])
    print ("reg_date = ", content["reg_date"])
    return 'JSON posted'
   
app.run(host = '0.0.0.0', port = 8000)