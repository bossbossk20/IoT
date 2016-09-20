var express = require('express')
var app = express()

app.post('/koy', (req, res) => {
  console.log(req)
})

app.listen(7777, () => {
  console.log('running on port 7777')
})
