<!DOCTYPE html>
<html>
  <head>
    <title>Quadratic Solver </title>
  </head>
  <body>
    <h2> Input the Coefficients of a Quadratic Equation </h2>
    <hr>
    <form method="get" action="/quadratic">
      <label>a <input name="a" type="text", value="{{repr(a)}}"> </label>
      <label>b <input name="b" type="text", value="{{repr(b)}}"> </label>
      <label>c <input name="c" type="text", value="{{repr(c)}}"> </label>
      <input type="submit" value="Submit">
    </form>
    <hr>
    <dl>
      <dt> Solve the equation: </dt>
      <dd> <code> {{repr(a)}} x&sup2; + {{repr(b)}} x + {{repr(c)}} = 0.0 </code> </dd>

      <dt> First root: </dt>
      <dd> <code> {{repr(x1)}} </code> </dd>

      <dt> Second root: </dt>
      <dd> <code> {{repr(x2)}} </code> </dd>
    </dl>
  </body>
</html>

