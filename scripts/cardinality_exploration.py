import pandas

"""
l_shipdate >= date '1994-01-01'
    AND l_shipdate < date '1994-01-01' + interval '1' year
    AND l_discount between 0.06 - 0.01 AND 0.06 + 0.01
    AND l_quantity < 24;

############ RESULTS #############
Cardinalities first stage all data:
ship_date 1:    43280900
ship_date 2:    25804316
discount:       16361562
quantity:       27590885

Cardinalities first stage small data:
ship_date 1:    4342
ship_date 2:    2584
discount:       1666
quantity:       2780

--> small data is a sufficient subset --> results of later stages only on small data

With that we come to the conclusion:
FINAL ORDER QUERY 6: discount, ship_date 2, ship_date 1, quantity

##################################
"""
LARGE_DATA = False

if (LARGE_DATA):
    df_filtered_ship_date1 = 0
    df_filtered_ship_date2 = 0
    df_filtered_discount = 0
    df_filtered_quantity = 0

    chunks = pandas.read_table('lineitem.tbl', comment='#', delimiter="|", chunksize=1000000)
    for df in chunks:
        df.columns = ['_', '_', '_', '_', 'quantity', '_', 'discount', '_', '_', '_', 'ship_date', '_', '_', '_', '_', '_', '_']
        df_filtered_ship_date1 += len(df[(df.ship_date >= '1994-01-01')])
        df_filtered_ship_date2 += len(df[(df.ship_date < '1995-01-01')])
        df_filtered_discount += len(df[(df.discount >= 0.05) & (df.discount <= 0.07)])
        df_filtered_quantity += len(df[(df.quantity < 24)])

        print(df_filtered_ship_date1)
        print(df_filtered_ship_date2)
        print(df_filtered_discount)
        print(df_filtered_quantity)

df = pandas.read_table('lineitemShort.tbl', comment='#', delimiter="|")
df.columns = ['_', '_', '_', '_', 'quantity', '_', 'discount', '_', '_', '_', 'ship_date', '_', '_', '_', '_', '_', '_']
print("Original length: " + str(len(df)))

print("\nFIRST STAGE:")
df_filtered_ship_date1 = df[(df.ship_date >= '1994-01-01')]
print("ship_date filter 1: " + str(len(df_filtered_ship_date1)))

df_filtered_ship_date2 = df[(df.ship_date < '1995-01-01')]
print("ship_date filter 2: " + str(len(df_filtered_ship_date2)))

df_filtered_discount = df[(df.discount >= 0.05) & (df.discount <= 0.07)]
print("discount filter: " + str(len(df_filtered_discount)))

df_filtered_quantity = df[(df.quantity < 24)]
print("quantity filter: " + str(len(df_filtered_quantity.quantity)))

print("\nSECOND STAGE (with discount as first):")
df_filtered_ship_date1 = df_filtered_discount[(df_filtered_discount.ship_date >= '1994-01-01')]
print("ship_date filter 1: " + str(len(df_filtered_ship_date1)))

df_filtered_ship_date2 = df_filtered_discount[(df_filtered_discount.ship_date < '1995-01-01')]
print("ship_date filter 2: " + str(len(df_filtered_ship_date2)))

df_filtered_quantity = df_filtered_discount[(df_filtered_discount.quantity < 24)]
print("quantity filter: " + str(len(df_filtered_quantity.quantity)))


print("\nTHIRD STAGE (with ship_date 2 as second):")
df_filtered_ship_date1 = df_filtered_ship_date2[(df_filtered_ship_date2.ship_date >= '1994-01-01')]
print("ship_date filter 1: " + str(len(df_filtered_ship_date1)))

df_filtered_quantity = df_filtered_ship_date2[(df_filtered_ship_date2.quantity < 24)]
print("quantity filter: " + str(len(df_filtered_quantity.quantity)))


print("\nFOURTH STAGE (with ship_date 1 as third):")
df_filtered_quantity = df_filtered_ship_date1[(df_filtered_ship_date1.quantity < 24)]
print("quantity filter: " + str(len(df_filtered_quantity.quantity)))

print("\n ------ FINAL ORDER QUERY 6: discount, ship_date 2, ship_date 1, quantity ------ ")

