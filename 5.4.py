
from netmiko import ConnectHandler

myserver = {
    'device_type': 'linux',
    'host':   '192.168.8.109',  #Your Server IP
    'username': 'kenggz', #your Server Username
    'password': '0147258', #your server password
    'port' : 22,
    'secret': '',
}

net_connect = ConnectHandler(**myserver)
output = net_connect.send_command('uname -a')
print(output)
