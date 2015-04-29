#import re for regular expression fuction
#import ast for convert string to dict 
# lina yi  date :04/ 23/ 2015 email : ly783@nyu.edu
import re
import ast
#convert the data in the blocknumber from string to appropriate dict in three certain Situation
def deserializedata(blocknumber):
  f = open('fusedata.'+str(blocknumber), 'r')
  datastring = f.read() 
  f.close()
  #if the data is dictionary 
  pattern_directory = re.compile(r'filename_to_inode_dict')
  match = pattern_directory.search(datastring)
  #if the data is a file
  pattern_file = re.compile(r'location')
  match1 = pattern_file.search(datastring)
  #if the data is super block
  pattern_superblock = re.compile(r'creationTime')
  match2 = pattern_superblock.search(datastring)
  #if the data is dictionary 
  if match:
    num = re.compile(r'\d+')
    a = num.findall(datastring)
    searchbrace = re.compile(r'{.*?}')
    filename_to_inode_dict=searchbrace.findall(datastring[1:])
    split_filename_to_inode_dict = filename_to_inode_dict[0].split(',')
    searchtype = re.compile(r':.*?:\d+')
    dict_dictionary= {'size':a[0],'uid':a[1],'gid':a[2],'mode':a[3],'atime':a[4],'ctime':a[5],'mtime':a[6],'linkcount':a[7]}
    file_to_inode_dict={}
    for x in range(len(split_filename_to_inode_dict)):
        a1= searchtype.findall(split_filename_to_inode_dict[x])
        aa = a1[0].split(':')
        file_to_inode_dict[aa[1]]=aa[2]
    dict_dictionary['filename_to_inode_dict'] = file_to_inode_dict
    return dict_dictionary
  #if the data is a file
  elif match1:
      num = re.compile(r'\d+')
      b= num.findall(datastring)
      dict_file = {'size':b[0],'uid':b[1],'gid':b[2],'mode':b[3],'linkcount':b[4],'atime':b[5],'ctime':b[6],'mtime':b[7],'indirect':b[8],'location':b[9]}
      return dict_file
  #if the data is super block
  elif match2:
      num2 = re.compile(r'\d+')
      c = num2.findall(datastring)
      super_dic = {'creationTime': c[0], 'mounted': c[1], 'devId':c[2], 'freeStart':c[3], 'freeEnd':c[4], 'root':c[5], 'maxBlocks':c[6]}
      return super_dic   
  else:
      return {} 
#check The DeviceID is correct
def check_Device_ID():
  file_device = deserializedata(0)
  if file_device['devId']!=20:
      print 'Device ID is not correct'
#check All times are in the past, nothing in the future
def check_Time():
  file_device = deserializedata(0)
  if file_device['creationTime']>1393630836:
      print 'Creation Time is not correct' 
  check_time_helper(26)
 
def check_time_helper(blocknumber):
  blockdata = deserializedata(blocknumber)
  if blockdata['atime']>1393630836 or blockdata['ctime']>1393630836 or blockdata['mtime']>1393630836:
      print 'The block', blocknumber, 'has wrong time'
  elif 'filename_to_inode_dict' not in blockdata:
      return 0
  else:
      block_dict = blockdata['filename_to_inode_dict']   
      for item in block_dict:
          if item!='..' and item!='.':
              check_time_helper(block_dict[item])
#Validate that the free block list is accurate includes           
def check_Freeblock():
#create a array with 10000 of 0
  flist=[0 for i in range (10000)]
  for i in range (1,26):
      f = open('fusedata.'+str(i), 'r')
      datastring = f.read() 
      f.close()
      #find the first index without space before 
      for c in range (0, len(datastring)):
        if datastring[c] != ' ':
          break
      #convert the string into flist_dic
      flist_dic = ast.literal_eval(datastring[c:])
      #input the number in datastring to appropriate index and successfully build the flist_dic
      for j in range(len(flist_dic)):
        flist[flist_dic[j]]=flist_dic[j]
  #for 10000 number of array check if each of them equals to 0      
  for z in range(10000):
    if flist[z] ==0:
      fi = open('fusedata.'+str(z), 'r')
      data = fi.read()
      fi.close()
      #check if it eqals to 4096 zero
      if data ==4096*'0':
        print 'The block',z, 'is free block'
    elif flist[z] != 0:
      fi = open('fusedata.'+str(z), 'r')
      data = fi.read()
      fi.close()
      if data!= 4096*'0':
        print 'The block',z, 'is not free block'
          
#check the directory contains . and ..
def check_dir():
  rootdata = deserializedata(26)
  if 'filename_to_inode_dict' not in rootdata:
      print 'root dir is Wrong'
      return 0
  else:
      check_dir_helper(26)
      
              
def check_dir_helper(blocknumber):
  blockdata = deserializedata(blocknumber) 
  if 'filename_to_inode_dict' not in blockdata:
      return 0
  block_dict = blockdata['filename_to_inode_dict']
  if '..' not in block_dict or '.'not in block_dict:
      print 'The block',blocknumber,'does not contain . or ..'    
  if block_dict['.']!=blocknumber:
      print 'The block',blocknumber,' . number is not correct'
  block1 = deserializedata(block_dict['..'])
  if 'filename_to_inode_dict' not in block1:
      print 'The block',blocknumber,' .. number is not correct'
  else:
      if blocknumber not in block1['filename_to_inode_dict'].values():
          print 'The block',blocknumber,' .. number is not correct'
  for item in block_dict:
      if item!='..' and item!='.':
          check_dir_helper(block_dict[item])

#check linkcount of each directory
def check_Link(blocknumber):
  blockdata = deserializedata(blocknumber)
  if 'filename_to_inode_dict' not in blockdata:
      return 0
  block_dict = blockdata['filename_to_inode_dict']   
  if blockdata['linkcount']!=len(block_dict):
      print 'The block',blocknumber,'has the wrong number of links' 
  for item in block_dict:
      if item!='..' and item!='.':
          check_Link(block_dict[item])

#check the indirect number  
def check_Indirect(blocknumber):
  blockdata = deserializedata(blocknumber)
  if 'filename_to_inode_dict' in blockdata:
      block_dict=blockdata['filename_to_inode_dict']  
      for item in block_dict:
          if item!='..' and item!='.':
              check_Indirect(block_dict[item])
  else:
       lblock = deserializedata(blockdata['location'])
       try:
           if len(lblock)>1 and blockdata['indirect']!=1:
               print 'The block',blocknumber,'has the wrong indirect'
       except TypeError:  
           if blockdata['indirect']!=0:  
               print 'The block',blocknumber,'has the wrong indirect'
      
#check if the size is valid for the number of block pointers in the location array    
def check_Size(blocknumber):      
  blockdata = deserializedata(blocknumber)
  if 'filename_to_inode_dict' in blockdata:
      block_dict=blockdata['filename_to_inode_dict']  
      for item in block_dict:
          if item!='..' and item!='.':
              check_Size(block_dict[item])
  else:
       if blockdata['indirect']==0:
           if blockdata['size']>4096:
               print 'The block',blocknumber,'has INVALID size'
           if blockdata['size']<0:
               print 'The block',blocknumber,'has INVALID size'  
       else:
           lblock = deserializedata(blockdata['location'])
           length = len(lblock)
           if blockdata['size']>4096*length or blockdata['size']<4096*(length-1):
               print 'The block',blocknumber,'has INVALID size'
           
check_Device_ID()
check_Time()
check_Freeblock()
check_dir()
check_Link(26)  
check_Indirect(26)
check_Size(26)
