var express = require('express')
var cors = require('cors')
var app = express()

app.use(cors())

app.get('/koy', (req, res)=> {
  res.send(4000)
})

app.post('/koy', (req, res) => {
  console.log(req)
})


app.listen(7777, () => {
  console.log('running on port 7777')
})
