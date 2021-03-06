import * as React from 'react'

// Components
import { ConnectWithSite } from '../components/extension'
import { WalletAccountType } from '../components/extension/connect-with-site-panel'
import { StyledExtensionWrapper } from './style'

export default {
  title: 'Wallet/Extension/Panels',
  parameters: {
    layout: 'centered'
  }
}

export const _ConnectWithSite = () => {
  const [selectedAccounts, setSelectedAccounts] = React.useState<WalletAccountType[]>([
    {
      id: '1',
      name: 'Account 1',
      address: '0x7d66c9ddAED3115d93Bd1790332f3Cd06Cf52B14'
    }
  ])
  const [readyToConnect, setReadyToConnect] = React.useState<boolean>(false)
  const url = 'https://app.uniswap.org'
  const accounts: WalletAccountType[] = [
    {
      id: '1',
      name: 'Account 1',
      address: '0x7d66c9ddAED3115d93Bd1790332f3Cd06Cf52B14'
    },
    {
      id: '2',
      name: 'Account 2',
      address: '0x73A29A1da97149722eB09c526E4eAd698895bDCf'
    },
    {
      id: '3',
      name: 'Account 3',
      address: '0x3f29A1da97149722eB09c526E4eAd698895b426'
    }
  ]
  const selectAccount = (account: WalletAccountType) => {
    const newList = [...selectedAccounts, account]
    setSelectedAccounts(newList)
  }
  const removeAccount = (account: WalletAccountType) => {
    const newList = selectedAccounts.filter(
      (accounts) => accounts.id !== account.id
    )
    setSelectedAccounts(newList)
  }
  const onSubmit = () => {
    alert(`Connecting to ${url} using: ${JSON.stringify(selectedAccounts)}`)
  }
  const primaryAction = () => {
    if (!readyToConnect) {
      setReadyToConnect(true)
    } else {
      onSubmit()
    }
  }
  const secondaryAction = () => {
    if (readyToConnect) {
      setReadyToConnect(false)
    } else {
      alert('You Clicked The Cancel Button!')
    }
  }
  return (
    <StyledExtensionWrapper>
      <ConnectWithSite
        siteURL={url}
        isReady={readyToConnect}
        accounts={accounts}
        primaryAction={primaryAction}
        secondaryAction={secondaryAction}
        selectAccount={selectAccount}
        removeAccount={removeAccount}
        selectedAccounts={selectedAccounts}
      />
    </StyledExtensionWrapper>
  )
}

_ConnectWithSite.story = {
  name: 'Connect With Site'
}
