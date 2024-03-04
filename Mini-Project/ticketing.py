import tkinter as tk
from tkinter import ttk, messagebox

class Ticket:
    def __init__(self, event_name, price, quantity):
        self.event_name = event_name
        self.price = price
        self.quantity = quantity

class TicketBookingSystem:
    def __init__(self):
        self.tickets = []

    def add_ticket(self, event_name, price, quantity):
        new_ticket = Ticket(event_name, price, quantity)
        self.tickets.append(new_ticket)
        messagebox.showinfo("Success", f"Ticket for {event_name} added successfully!")

    def display_tickets(self):
        if not self.tickets:
            messagebox.showinfo("No Tickets", "No tickets available.")
        else:
            ticket_info = "Available Tickets:\n"
            for ticket in self.tickets:
                ticket_info += f"{ticket.event_name} - Price: {ticket.price} - Quantity: {ticket.quantity}\n"
            messagebox.showinfo("Ticket Information", ticket_info)

    def update_ticket(self, event_name, new_price, new_quantity):
        for ticket in self.tickets:
            if ticket.event_name == event_name:
                ticket.price = new_price
                ticket.quantity = new_quantity
                messagebox.showinfo("Success", f"Ticket information updated for {event_name}.")
                return
        messagebox.showwarning("Error", f"Ticket for {event_name} not found.")

    def delete_ticket(self, event_name):
        self.tickets = [ticket for ticket in self.tickets if ticket.event_name != event_name]
        messagebox.showinfo("Success", f"Ticket for {event_name} deleted successfully.")

def add_ticket_window():
    add_window = tk.Toplevel(root)
    add_window.title("Add Ticket")

    ttk.Label(add_window, text="Event Name:").pack()
    event_name_entry = ttk.Entry(add_window)
    event_name_entry.pack()

    ttk.Label(add_window, text="Price:").pack()
    price_entry = ttk.Entry(add_window)
    price_entry.pack()

    ttk.Label(add_window, text="Quantity:").pack()
    quantity_entry = ttk.Entry(add_window)
    quantity_entry.pack()

    def add_ticket():
        event_name = event_name_entry.get()
        price = float(price_entry.get())
        quantity = int(quantity_entry.get())
        ticket_system.add_ticket(event_name, price, quantity)
        add_window.destroy()

    ttk.Button(add_window, text="Add Ticket", command=add_ticket).pack()

def display_tickets():
    ticket_system.display_tickets()

def update_ticket_window():
    update_window = tk.Toplevel(root)
    update_window.title("Update Ticket")

    ttk.Label(update_window, text="Event Name:").pack()
    event_name_entry = ttk.Entry(update_window)
    event_name_entry.pack()

    ttk.Label(update_window, text="New Price:").pack()
    new_price_entry = ttk.Entry(update_window)
    new_price_entry.pack()

    ttk.Label(update_window, text="New Quantity:").pack()
    new_quantity_entry = ttk.Entry(update_window)
    new_quantity_entry.pack()

    def update_ticket():
        event_name = event_name_entry.get()
        new_price = float(new_price_entry.get())
        new_quantity = int(new_quantity_entry.get())
        ticket_system.update_ticket(event_name, new_price, new_quantity)
        update_window.destroy()

    ttk.Button(update_window, text="Update Ticket", command=update_ticket).pack()

def delete_ticket_window():
    delete_window = tk.Toplevel(root)
    delete_window.title("Delete Ticket")

    ttk.Label(delete_window, text="Event Name:").pack()
    event_name_entry = ttk.Entry(delete_window)
    event_name_entry.pack()

    def delete_ticket():
        event_name = event_name_entry.get()
        ticket_system.delete_ticket(event_name)
        delete_window.destroy()

    ttk.Button(delete_window, text="Delete Ticket", command=delete_ticket).pack()

root = tk.Tk()
root.title("Ticket Booking System")

ticket_system = TicketBookingSystem()

style = ttk.Style()
style.configure('TButton', font=('Arial', 12))

add_button = ttk.Button(root, text="Add Ticket", command=add_ticket_window)
add_button.pack(pady=10)

display_button = ttk.Button(root, text="Display Tickets", command=display_tickets)
display_button.pack(pady=10)

update_button = ttk.Button(root, text="Update Ticket", command=update_ticket_window)
update_button.pack(pady=10)

delete_button = ttk.Button(root, text="Delete Ticket", command=delete_ticket_window)
delete_button.pack(pady=10)

exit_button = ttk.Button(root, text="Exit", command=root.destroy)
exit_button.pack(pady=10)

root.mainloop()
