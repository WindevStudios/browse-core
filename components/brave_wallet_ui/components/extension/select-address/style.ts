import styled from 'styled-components'
import CheckIcon from '../assets/filled-checkmark.svg'
import Blockies from '../assets/blockies-temp.svg'

export const StyledWrapper = styled.div`
  display: flex;
  align-items: center;
  justify-content: space-between;
  flex-direction: row;
  width: 100%;
  cursor: pointer;
  padding: 0px 12px;
  padding-bottom: 8px;
`

export const NameAndAddressColumn = styled.div`
  display: flex;
  align-items: flex-start;
  justify-content: flex-start;
  flex-direction: column;
  margin-left: 12px;
`

export const LeftSide = styled.div`
  display: flex;
  align-items: center;
  justify-content: flex-start;
  flex-direction: row;
`
// Need to add blockies package
export const AccountCircle = styled.div`
	width: 40px;
	height: 40px;
	border-radius: 100%;
	background: url(${Blockies});
`

export const AccountNameText = styled.span`
	font-family: Poppins;
	font-size: 13px;
	line-height: 20px;
	font-weight: 600;
`

export const AccountAddressText = styled.span`
	font-family: Poppins;
	font-size: 12px;
	line-height: 18px;
	font-weight: 400;
`

export const UnSelectedCircle = styled.div`
	width: 24px;
	height: 24px;
	border-radius: 24px;
	border: 1px solid ${(p) => p.theme.color.inputBorder};
`
// I added this SVG icon for now, will change once added to brave-ui
export const SelectedIcon = styled.div`
	width: 24px;
	height: 24px;
	background: url(${CheckIcon});
`
