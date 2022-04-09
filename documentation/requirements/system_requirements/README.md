# <span style="color:#33cc33">System requirements (DRAFT)</span>

This document contains system requirements, specifying system elements and their functionality.

# <span style="color:#33cc33">System structure / elements</span>

## <span style="color:#6666ff">SYS_G95BR</span>

There shall be an electronic element (later called EE in this document) responsible for performing data acquisition.

OUT links:
 - [PDD_PC2RX](/documentation/requirements/product_requirements/README.md#pddpc2rx)

IN links:
 - None (yet).

---

## <span style="color:#6666ff">SYS_E7SAE</span>

There shall be a wireless network router provided in the system for networking needs.

OUT links:
 - [PDD_VCCLV](/documentation/requirements/product_requirements/README.md#pddvcclv)
 - [PDD_E6XDY](/documentation/requirements/product_requirements/README.md#pdde6xdy)

IN links:
 - None (yet).

---

## <span style="color:#6666ff">SYS_KNDEL</span>

The user shall use their smarphone to interact with the system and receive information from the system.

OUT links:
 - [PDD_E6XDY](/documentation/requirements/product_requirements/README.md#pdde6xdy)
 - [PDD_U4MO3](/documentation/requirements/product_requirements/README.md#pddu4mo3)

IN links:
 - None (yet).

---

## <span style="color:#6666ff">SYS_707PJ</span>

There shall be a cloud service responsible for storing the data and performing necessary calculations.

OUT links:
 - [PDD_VCCLV](/documentation/requirements/product_requirements/README.md#pddvcclv)
 - [PDD_U4MO3](/documentation/requirements/product_requirements/README.md#pddu4mo3)

IN links:
 - None (yet).

---

## <span style="color:#6666ff">SYS_VXAJN</span>

There shall be an app/cloud service allowing for sending notifications to user.

OUT links:
 - [PDD_E6XDY](/documentation/requirements/product_requirements/README.md#pdde6xdy)

IN links:
 - None (yet).

---

# <span style="color:#33cc33">System element - electronic element</span>

## <span style="color:#6666ff">SYS_5PFPI</span>

The responsibilities of the EE shall be as follows:
 - acquisition of environmental data: temperature, humidity and ambient lighting,
 - basic configuration of user notification event triggers,
 - secure establishment of connection with wireless network router,
 - secure data posting to external cloud-based service.

OUT links:
 - [PDD_PC2RX](/documentation/requirements/product_requirements/README.md#pddpc2rx)
 - [PDD_U4MO3](/documentation/requirements/product_requirements/README.md#pddu4mo3)

IN links:
 - None (yet).

---

## <span style="color:#6666ff">SYS_FNGQS</span>

EE shall be designed so that it consumes the least energy possible while maintaining all the necessary functionalities.

OUT links:
 - [PDD_P64II](/documentation/requirements/product_requirements/README.md#pddp64ii)

IN links:
 - None (yet).

---

## <span style="color:#6666ff">SYS_PUKUO</span>

EE shall be placed on the wall of the terrarium and must be designed accordingly.

OUT links:
 - [PDD_3WHWZ](/documentation/requirements/product_requirements/README.md#pdd3whwz)

IN links:
 - None (yet).

---

# <span style="color:#33cc33">System element - wireless network router</span>

## <span style="color:#6666ff">SYS_GPQF4</span>

The router should be compatible with sufficient WiFi standard - at least IEEE 802.11n.

OUT links:
 - [PDD_3LFZWM](/documentation/requirements/product_requirements/README.md#pdd3lfzwm)

IN links:
 - None (yet).

---

# <span style="color:#33cc33">System element - smartphone</span>

## <span style="color:#6666ff">SYS_6UYZY</span>

User's smartphone shall have access to internet in order to receive up-to-date notifications from EE.

OUT links:
 - [PDD_E6XDY](/documentation/requirements/product_requirements/README.md#pdde6xdy)
 - [PDD_U4MO3](/documentation/requirements/product_requirements/README.md#pddu4mo3)

IN links:
 - None (yet).

---

## <span style="color:#6666ff">SYS_TMWWR</span>

User's smartphone shall be able to run software needed for notification service.

OUT links:
 - [PDD_3LFZWM](/documentation/requirements/product_requirements/README.md#pdd3lfzwm)

IN links:
 - None (yet).

---

# <span style="color:#33cc33">System element - cloud data management service</span>

## <span style="color:#6666ff">SYS_8N4ZN</span>

The service used shall be ThingSpeak, for its simplicity and possibilities.

Please note that the exact service setup will be described in separate document, outside of requirements.

OUT links:
 - [PDD_VCCLV](/documentation/requirements/product_requirements/README.md#pddvcclv)
 - [PDD_E6XDY](/documentation/requirements/product_requirements/README.md#pdde6xdy)

IN links:
 - [ThingSpeak description and setup](/documentation/thingspeak/README.md)

---

# <span style="color:#33cc33">System element - notification service</span>

## <span style="color:#6666ff">SYS_M8V15</span>

The service used shall be IFTTT, because of very easy integration with data processing service and ready-made application for mobile devices.

Please note that the exact service setup will be described in separate document, outside of requirements.

OUT links:
 - [PDD_E6XDY](/documentation/requirements/product_requirements/README.md#pdde6xdy)
 - [PDD_3WHWZ](/documentation/requirements/product_requirements/README.md#pdd3whwz)

IN links:
 - [IFTTT description and setup](/documentation/ifttt/README.md)

---
