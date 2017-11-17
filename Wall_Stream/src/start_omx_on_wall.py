from paramiko import SSHClient, AutoAddPolicy

def Connect(ip, username='pi', pw='password'): 
    '''ssh into the pi'''
    print('connecting to {}@{}...'.format(username, ip))
    ssh = SSHClient()
    ssh.set_missing_host_key_policy(AutoAddPolicy())
    ssh.connect(ip, username=username, password=pw)
    print('connection status =', ssh.get_transport().is_active())
    return ssh

def SendCommand(ssh, command, pw='password'):
    '''send a terminal/bash command to the ssh'ed-into machine '''
    print('sending a command... ', command)
    ssh.exec_command( command )


myssh = Connect(ip='192.168.60.241', pw='Wbhdvc2017!')
SendCommand(myssh, command='python start_wall.py')

