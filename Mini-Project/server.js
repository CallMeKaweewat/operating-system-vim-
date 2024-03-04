const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const port = 3000;

app.use(bodyParser.urlencoded({ extended: true }));

// Mock Database for Ticket Inventory
let ticketInventory = {
  regular: 100,
  vip: 50
};

// Endpoint for Ticket Purchase
app.post('/purchase', (req, res) => {
  const { ticketType, quantity } = req.body;

  if (!ticketType || !quantity || isNaN(quantity) || quantity <= 0) {
    return res.status(400).send('Invalid input');
  }

  if (ticketInventory[ticketType] < quantity) {
    return res.status(400).send('Not enough tickets available');
  }

  // Process Purchase (e.g., deduct tickets from inventory, handle payment, etc.)
  ticketInventory[ticketType] -= quantity;

  // Return success message
  res.status(200).send(`Successfully purchased ${quantity} ${ticketType} ticket(s)`);
});

app.listen(port, () => {
  console.log(`Server is running at http://localhost:${port}`);
});
