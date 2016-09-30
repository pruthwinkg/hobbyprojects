from bottle import *
import time
import algebra
import monkey_patching

@route('/')
def welcome():
    response.set_header('Cache-Control', 'max-age=15')
    if 'text/html' in request.headers.get('Accept', '*/*'):
        response.content_type = 'text/html'
        return '<h1> Howdy! </h1>'
    response.content_type = 'text/plain'
    return 'Hi ya!'

@route('/now')
def time_micro_service():
    response.content_type = 'text/plain'
    return time.ctime()

@route('/upper/<word>')
def uppercase_service(word):
    response.content_type = 'text/plain'
    return word.upper()

@route('/area/circle')
def circle_area_service():
    response.set_header('Cache-Control', 'max-age=15')
    try:
        radius = float(request.query.get('radius', '0.0'))
    except ValueError:
        return dict(error='Must supply a floating point radius')
    area = algebra.area(radius)
    return dict(area=area, radius=radius, service=request.path)

@route('/quad')
def show_form():
    return template('day2/notes2/quadratic.tpl', a=0, b=0, c=0, x1=0, x2=0)


@route('/quadratic')
def quadratic_service():
    # http://localhost:8080/quadratic?a=25&b=80&c=4
    try:
        a = float(request.query.get('a', '0.0'))
        b = float(request.query.get('b', '0.0'))
        c = float(request.query.get('c', '0.0'))
    except ValueError:
        return dict(error='Must supply a floating point radius')
    x1, x2 = algebra.quadratic(a, b, c)
    return template('day2/notes2/quadratic.tpl', a=a, b=b, c=c, x1=x1, x2=x2)

if __name__ == '__main__':

    run(host='localhost', port=8080)
