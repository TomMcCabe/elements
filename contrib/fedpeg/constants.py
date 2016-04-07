#!/usr/bin/env python2

import os

class FedpegConstants:
	# VARIOUS SETTINGS...
	sidechain_url = "http://tommccabe:0c4GwXdXzxl3@127.0.0.1:4251"
	bitcoin_url = "http://tommccabe:0c4GwXdXzxl3@127.0.0.1:18332"

	#creating 2-of-2 multisig with private keys on same machine
	redeem_script = "5221023c4d01013fef44f5b567e4cbf426bdd92269667e77e0f551478ac1ad183f63d921020f2d896cb31ed5e63e5a1ea3f1d80377274dccdd61fef1a213d1ed41ac981ffa52ae"
	redeem_script_address = "2MwY9t6panKw7eEp2vxPErupQyTxC6k5KGx"
	secondScriptPubKeyHash = "9eac001049d5c38ece8996485418421f4a01e2d7"

	blocksigning_private_key = "cVUHLAQKyQJZorHx8GBwf3Y5fMYfBVsxTagJMm2s1xvh3BPPDb6t"
	functionary_private_key = "cNC314P57jkS8JGFqZDN4bxL83YXC873g4V4QAJMNXue3HLbA2wf"

	bitcoin_tx_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../../bitcoin-tx")
	contracthashtool_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../../contracthashtool/contracthashtool")
	is_testnet = 1

	#Bitcoin:
	bitcoin_genesis_hash = "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"
	#Testnet:
	#bitcoin_genesis_hash = "000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943"

	nodes =["192.168.1.115", "192.168.1.172"]
	my_node = "192.168.1.115"

	# Set this to non-None if you're using a proxy (eg for Tor)
	# Note that this requires ZMQ 4.1
	socks_proxy = None
	#socks_proxy = "127.0.0.1:9050"

	def __init__(self):
		# Derived constants (dont touch)
		self.testnet_arg = ""
		if self.is_testnet == 1:
			self.cht_testnet_arg = "-t"
			self.btc_testnet_arg = "-testnet"
		else:
			self.cht_testnet_arg = ""
			self.btc_testnet_arg = ""

		self.sigs_required = int(self.redeem_script[:2], 16) - 0x50

		self.inverse_bitcoin_genesis_hash = "".join(reversed([self.bitcoin_genesis_hash[i:i+2] for i in range(0, len(self.bitcoin_genesis_hash), 2)]))
