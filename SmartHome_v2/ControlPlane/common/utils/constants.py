# Service names
AUTHENTICATION = 'authentication'
INFRA = 'infra'

# Port numbers of various services. Make sure it is consistent with the docker-compose.yml
INFRA_PORT = 9001
WEB_APP_PORT = 9002
AUTHENTICATION_PORT = 9003

# Service URL prefix
AUTHENTICATION_PREFIX = '/authentication/internal'
INFRA_PREFIX = '/infra/debug/'

# Various service URLs
AUTHENTICATION_URL = 'http://' + AUTHENTICATION + ':' + str(AUTHENTICATION_PORT) + AUTHENTICATION_PREFIX
INFRA_URL = 'http://' + INFRA + ':' + str(INFRA_PORT) + INFRA_PREFIX


# AUTHENTICATION ENDPOINTS
AUTHENTICATION_EP_CREATE_PROFILES = '/create_profile'
AUTHENTICATION_EP_DELETE_PROFILES = '/delete_profiles'
AUTHENTICATION_EP_UPDATE_PROFILES = '/update_profiles'
AUTHENTICATION_EP_LIST_PROFILES = '/list_profiles'

AUTHENTICATION_EP_CREATE_USERS = '/create_user'
AUTHENTICATION_EP_DELETE_USERS = '/delete_users'
AUTHENTICATION_EP_UPDATE_USERS = '/update_users'
AUTHENTICATION_EP_LIST_USERS = '/list_users'

AUTHENTICATION_EP_USER_LOGIN = "/login"


# INFRA ENDPOINTS
INFRA_EP_DROP_TABLE = '/drop_table'
INFRA_EP_LIST_TABLES = '/list_tables'
INFRA_EP_RECREATE_TABLES = '/recreate_tables'