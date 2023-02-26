import json
import time

import boto3


client = boto3.client("lambda")

function_name = "test"

total_duration = 0
n = 10
for i in range(n):
    payload = {
        "message": f"Hello World {i}!",
    }
    print(payload)
    start_time = time.time()
    response = client.invoke(
        FunctionName=function_name,
        InvocationType="RequestResponse",
        Payload=json.dumps(payload),
    )
    end_time = time.time()
    duration = end_time - start_time
    print("Duration:", duration, "s")
    print(json.loads(response["Payload"].read()))
    total_duration += duration
print("Average Duration:", total_duration / n, "s")