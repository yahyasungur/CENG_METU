from stacknqueue import *

def a_day_at_an_atm(t_end, customers):
    queue = CreateQueue()
    ci = 0
    for t in range(t_end + 1):  # simulate t_end steps up until t_end
        if IsEmptyQueue(queue) == False:  # process the customer at the ATM
            Front(queue)[1] -= 1    # reduce t_usage of the customer at the ATM
            if Front(queue)[1] == 0:  # customer is done, remove from queue
                Dequeue(queue) 
        while ci < len(customers) and t == customers[ci][1]: # add new customers
            name, _, t_usage = customers[ci]
            Enqueue([name, t_usage], queue)
            ci += 1
    return [name for name, _ in queue]

#print(a_day_at_an_atm(0, [('ahmet', 0, 10)]))  # ahmet arrives at the queue at 0
#['ahmet']
#print(a_day_at_an_atm(0, [('ahmet', 0, 10), ('feyza', 0, 3)])) # both arrive at the queue at 0
#['ahmet', 'feyza']
#print(a_day_at_an_atm(9, [('ahmet', 0, 10)])) # ahmet has been at the atm for 9, needs 10
#['ahmet']
#print(a_day_at_an_atm(10, [('ahmet', 0, 10)])) # ahmet is done at t=10 and goes away
#[]
#print(a_day_at_an_atm(5, [('ahmet', 0, 10), ('feyza', 0, 3), ('abdullah', 4, 5)])) # abdullah arrived at 4
#['ahmet', 'feyza', 'abdullah']
#print(a_day_at_an_atm(10, [('ahmet', 0, 10), ('feyza', 0, 3), ('abdullah', 4, 5)])) # ahmet is done at 10
#['feyza', 'abdullah']
#print(a_day_at_an_atm(15, [('ahmet', 0, 10), ('feyza', 0, 3), ('abdullah', 4, 5)])) # feyza was done at 13
#['abdullah']
#print(a_day_at_an_atm(30, [('ahmet', 0, 10), ('feyza', 0, 3), ('abdullah', 4, 5)])) # abdullah was done at 17
#[]